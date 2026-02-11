mpu6500SetSlaveOutputByte(uint8_t num, uint8_t data)
{
  if (num > 3)
    return;
  i2cdevWriteByte(I2Cx, devAddr, MPU6500_RA_I2C_SLV0_DO + num, data);
}
