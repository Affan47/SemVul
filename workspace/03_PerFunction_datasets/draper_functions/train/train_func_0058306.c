byte_order_test(void)
{
  u_16bit_t test = TRANSFER_REGET_PACKETID;

  if (*((u_8bit_t *) & test) == ((TRANSFER_REGET_PACKETID & 0xff00) >> 8))
    return 0;
  if (*((u_8bit_t *) & test) == (TRANSFER_REGET_PACKETID & 0x00ff))
    return 1;
  return 0;
}
