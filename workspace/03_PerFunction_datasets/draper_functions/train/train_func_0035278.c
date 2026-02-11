update_CRC (const guint data, const guint length, guint * crc)
{
  unsigned int masking, carry;

  masking = 1 << length;

  while ((masking >>= 1)) {
    carry = *crc & 0x8000;
    *crc <<= 1;
    if (!carry ^ !(data & masking))
      *crc ^= CRC16_POLYNOMIAL;
  }
  *crc &= 0xffff;
}
