calc_checksum (const uint16_t * data, unsigned int bytes)
{
  uint32_t sum;
  unsigned int i;

  sum = 0;
  for (i = 0; i < bytes / 2; i++)
    sum += data[i];
  sum = (sum & 0xffff) + (sum >> 16);
  sum = htons (0xffff - sum);
  return sum;
}
