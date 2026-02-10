i2cdevWrite(I2C_Dev *dev, uint8_t devAddress, uint8_t memAddress,
                uint16_t len, uint8_t *data)
{
  dev->pCPAL_TransferTx->wNumData = len;
  dev->pCPAL_TransferTx->pbBuffer = data;
  dev->pCPAL_TransferTx->wAddr1 = devAddress << 1;
  dev->pCPAL_TransferTx->wAddr2 = memAddress;

  if (memAddress != I2CDEV_NO_MEM_ADDR)
  {
    dev->wCPAL_Options &= !CPAL_OPT_NO_MEM_ADDR;
  }
  else
  {
    dev->wCPAL_Options |= CPAL_OPT_NO_MEM_ADDR;
  }

  return i2cdevWriteTransfer(dev);
}
