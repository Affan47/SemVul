ak8963Init(I2C_Dev *i2cPort)
{
  if (isInit)
    return;

  I2Cx = i2cPort;
  devAddr = AK8963_ADDRESS_00;
}
