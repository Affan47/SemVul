ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState)
{
  uint32_t itmask = 0;

  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_IT(ADC_IT));


  itmask = (uint8_t)ADC_IT;
  itmask = (uint32_t)0x01 << itmask;

  if (NewState != DISABLE)
  {

    ADCx->CR1 |= itmask;
  }
  else
  {

    ADCx->CR1 &= (~(uint32_t)itmask);
  }
}
