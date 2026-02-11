GNUNET_CRYPTO_crc16_step (uint32_t sum, const void *buf, size_t len)
{
  const uint16_t *hdr = buf;
  for (; len >= 2; len -= 2)
    sum += *(hdr++);
  if (len == 1)
    sum += (*hdr) & ntohs(0xFF00);
  return sum;
}
