yubikey_crc16 (const unsigned char *buf, size_t buf_size)
{
  unsigned short m_crc = 0xffff;

  while (buf_size--)
    {
      int i, j;
      m_crc ^= (unsigned char) * buf++ & 0xFF;
      for (i = 0; i < 8; i++)
	{
	  j = m_crc & 1;
	  m_crc >>= 1;
	  if (j)
	    m_crc ^= 0x8408;
	}
    }

  return m_crc;
}
