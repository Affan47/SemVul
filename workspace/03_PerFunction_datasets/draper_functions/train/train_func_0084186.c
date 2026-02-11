sdioLowLevelInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	memset((void *)&sdioData, 0, sizeof(sdioData));

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_SDIO);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_SDIO);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SDIO);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SDIO);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SDIO);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_SDIO);


	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SDIO, ENABLE);

#ifdef SDIO_POWER_PORT

	sdioData.sdEnable = digitalInit(SDIO_POWER_PORT, SDIO_POWER_PIN, 0);
#endif


	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel = SDIO_DMA_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	extRegisterCallback(SDIO_DETECT_GPIO_PORT, SDIO_DETECT_PIN, EXTI_Trigger_Rising_Falling, 2, GPIO_PuPd_UP, sdioIntHandler);

	sdioData.initialized = 0;
	sdioData.cardRemovalMicros = 0;

	if (SD_DetectLowLevel() == SD_NOT_PRESENT) {
		sdioData.cardRemovalMicros = timerMicros();
	}
#ifdef SDIO_POWER_PORT
	else {
		digitalHi(sdioData.sdEnable);
	}
#endif
}
