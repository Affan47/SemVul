ip_cksum_partial(m_uint8_t *buf,int len)
{
   m_uint32_t sum = 0;

   while(len > 1) {
      sum += ((m_uint16_t)buf[0] << 8) | buf[1];
      buf += sizeof(m_uint16_t);
      len -= sizeof(m_uint16_t);
   }

   if (len == 1)
      sum += (m_uint16_t)(*buf) << 8;

   return(sum);
}
