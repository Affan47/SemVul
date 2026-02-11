motorsInit(const MotorPerifDef** motorMapSelect)
{
  int i;

  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  if (isInit)
  {
    motorsDeInit(motorMap);
  }

  motorMap = motorMapSelect;

  for (i = 0; i < NBR_OF_MOTORS; i++)
  {

    MOTORS_RCC_GPIO_CMD(motorMap[i]->gpioPerif, ENABLE);
    MOTORS_RCC_TIM_CMD(motorMap[i]->timPerif, ENABLE);


    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = MOTORS_GPIO_MODE;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef PLATFORM_CF2
    GPIO_InitStructure.GPIO_OType = motorMap[i]->gpioOType;
#endif
    GPIO_InitStructure.GPIO_Pin = motorMap[i]->gpioPin;
    GPIO_Init(motorMap[i]->gpioPort, &GPIO_InitStructure);


    MOTORS_GPIO_AF_CFG(motorMap[i]->gpioPort, motorMap[i]->gpioPinSource, motorMap[i]->gpioAF);


    TIM_TimeBaseStructure.TIM_Period = motorMap[i]->timPeriod;
    TIM_TimeBaseStructure.TIM_Prescaler = motorMap[i]->timPrescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(motorMap[i]->tim, &TIM_TimeBaseStructure);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = motorMap[i]->timPolarity;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;


    motorMap[i]->ocInit(motorMap[i]->tim, &TIM_OCInitStructure);
    motorMap[i]->preloadConfig(motorMap[i]->tim, TIM_OCPreload_Enable);

    MOTORS_TIM_DBG_CFG(motorMap[i]->timDbgStop, ENABLE);

    TIM_CtrlPWMOutputs(motorMap[i]->tim, ENABLE);
  }


  for (i = 0; i < NBR_OF_MOTORS; i++)
  {
    TIM_Cmd(motorMap[i]->tim, ENABLE);
  }

  isInit = true;
}
