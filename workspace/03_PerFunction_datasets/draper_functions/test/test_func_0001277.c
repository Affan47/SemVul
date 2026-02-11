rtcInit(void) {
	RTC_InitTypeDef RTC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	unsigned long periodValue;

	memset((void *)&rtcData, 0, sizeof(rtcData));


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);


	PWR_BackupAccessCmd(ENABLE);

	RCC_LSICmd(ENABLE);


	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
		;


	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	RCC_RTCCLKCmd(ENABLE);


	RTC_WaitForSynchro();


	EXTI_ClearITPendingBit(EXTI_Line22);
	EXTI_InitStructure.EXTI_Line = EXTI_Line22;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RTC_WakeUpCmd(DISABLE);


	RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
	RTC_SetWakeUpCounter(0x0);


	RTC_WakeUpCmd(ENABLE);


	RTC_ClearITPendingBit(RTC_IT_WUT);
	RTC_ITConfig(RTC_IT_WUT, ENABLE);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);


	TIM_RemapConfig(TIM5, TIM5_LSI);


	TIM_PrescalerConfig(TIM5, 0, TIM_PSCReloadMode_Immediate);

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV8;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	TIM_Cmd(TIM5, ENABLE);


	TIM5->SR = 0;


	TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);


	while (rtcData.captureNumber < 2)
		;

	TIM_DeInit(TIM5);


	periodValue = (uint16_t)(0xFFFF - rtcData.captureLSI[0] + rtcData.captureLSI[1] + 1);


	rtcData.lsiFrequency = (((2 * rccClocks.PCLK1_Frequency / 1000000 * AQ_US_PER_SEC) / periodValue) * 8);

	rtcData.asyncPrediv = 4;
	rtcData.syncPrediv = (rtcData.lsiFrequency / (rtcData.asyncPrediv + 1)) - 1;


	RTC_InitStructure.RTC_AsynchPrediv = rtcData.asyncPrediv;
	RTC_InitStructure.RTC_SynchPrediv = rtcData.syncPrediv;
	RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	RTC_Init(&RTC_InitStructure);

	RTC_BypassShadowCmd(ENABLE);
	RTC_WriteProtectionCmd(DISABLE);

	RTC_EnterInitMode();
}
