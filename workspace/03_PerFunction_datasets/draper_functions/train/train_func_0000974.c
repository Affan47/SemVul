piezoInit()
{
  if (isInit)
    return;


  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;


  RCC_AHB1PeriphClockCmd(PIEZO_GPIO_POS_PERIF | PIEZO_GPIO_NEG_PERIF, ENABLE);
  RCC_APB1PeriphClockCmd(PIEZO_TIM_PERIF, ENABLE);


  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Pin = PIEZO_GPIO_POS_PIN;
  GPIO_Init(PIEZO_GPIO_POS_PORT, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = PIEZO_GPIO_NEG_PIN;
  GPIO_Init(PIEZO_GPIO_NEG_PORT, &GPIO_InitStructure);


  GPIO_PinAFConfig(PIEZO_GPIO_POS_PORT, PIEZO_GPIO_AF_POS_PIN, PIEZO_GPIO_AF_POS);
  GPIO_PinAFConfig(PIEZO_GPIO_NEG_PORT, PIEZO_GPIO_AF_NEG_PIN, PIEZO_GPIO_AF_NEG);


  TIM_TimeBaseStructure.TIM_Period = PIEZO_PWM_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = PIEZO_PWM_PRESCALE;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(PIEZO_TIM, &TIM_TimeBaseStructure);


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;


  TIM_OC3Init(PIEZO_TIM, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(PIEZO_TIM, TIM_OCPreload_Enable);


  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC4Init(PIEZO_TIM, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(PIEZO_TIM, TIM_OCPreload_Enable);


  TIM_CtrlPWMOutputs(PIEZO_TIM, ENABLE);
  TIM_SetCompare3(PIEZO_TIM, 0x00);
  TIM_SetCompare4(PIEZO_TIM, 0x00);


  TIM_Cmd(PIEZO_TIM, ENABLE);

  isInit = true;
}
