i2cdevWriteBits(I2C_Dev *dev, uint8_t devAddress, uint8_t memAddress,
                     uint8_t bitStart, uint8_t length, uint8_t data)
{
  bool status;
  uint8_t byte;

  if ((status = i2cdevReadByte(dev, devAddress, memAddress, &byte)) == true)
  {
      uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
      data <<= (bitStart - length + 1);
      data &= mask;
      byte &= ~(mask);
      byte |= data;
      status = i2cdevWriteByte(dev, devAddress, memAddress, byte);
  }

  return status;
}
