I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;


  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));


  i2cxbase = (uint32_t)I2Cx;


  i2creg = I2C_FLAG >> 28;


  I2C_FLAG &= FLAG_MASK;

  if(i2creg != 0)
  {

    i2cxbase += 0x14;
  }
  else
  {

    I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);

    i2cxbase += 0x18;
  }

  if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
  {

    bitstatus = SET;
  }
  else
  {

    bitstatus = RESET;
  }


  return  bitstatus;
}
