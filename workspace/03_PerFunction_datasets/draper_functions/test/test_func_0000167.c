USB_ReadEP (uint32_t EPNum, uint8_t *pData)
{
  uint32_t cnt, n;

  USB_CTRL = ((EPNum & 0x0F) << 2) | CTRL_RD_EN;

  delay( 5 );

  do
  {
    cnt = USB_RXPLEN;
  } while ((cnt & PKT_DV) == 0);
  cnt &= PKT_LNGTH_MASK;

  for (n = 0; n < (cnt + 3) / 4; n++)
  {
    *((uint32_t __attribute__((packed)) *)pData) = USB_RXDATA;
    pData += 4;
  }

  USB_CTRL = 0;

  if ((EPNum & 0x80) != 0x04)
  {
    WrCmdEP(EPNum, CMD_CLR_BUF);
  }

  return (cnt);
}
