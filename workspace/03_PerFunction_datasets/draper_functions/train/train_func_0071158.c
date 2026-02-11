I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;


  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));


  enablestatus = (uint32_t)(((I2C_IT & ITEN_MASK) >> 16) & (I2Cx->CR2)) ;


  I2C_IT &= FLAG_MASK;


  if (((I2Cx->SR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
  {

    bitstatus = SET;
  }
  else
  {

    bitstatus = RESET;
  }

  return  bitstatus;
}
