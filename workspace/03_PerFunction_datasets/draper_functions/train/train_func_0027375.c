TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;


  assert_param(IS_TIM_LIST1_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));


  TIMx->CCER &= (uint16_t)~TIM_CCER_CC1E;


  tmpccer = TIMx->CCER;

  tmpcr2 =  TIMx->CR2;


  tmpccmrx = TIMx->CCMR1;


  tmpccmrx &= (uint16_t)~TIM_CCMR1_OC1M;
  tmpccmrx &= (uint16_t)~TIM_CCMR1_CC1S;

  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;


  tmpccer &= (uint16_t)~TIM_CCER_CC1P;

  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;


  tmpccer |= TIM_OCInitStruct->TIM_OutputState;

  if((TIMx == TIM1) || (TIMx == TIM8))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));


    tmpccer &= (uint16_t)~TIM_CCER_CC1NP;

    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;

    tmpccer &= (uint16_t)~TIM_CCER_CC1NE;


    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;

    tmpcr2 &= (uint16_t)~TIM_CR2_OIS1;
    tmpcr2 &= (uint16_t)~TIM_CR2_OIS1N;

    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;

    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }

  TIMx->CR2 = tmpcr2;


  TIMx->CCMR1 = tmpccmrx;


  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;


  TIMx->CCER = tmpccer;
}
