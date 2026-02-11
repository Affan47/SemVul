ipv4_get_num_subnets(unsigned short int pfxlen,
                               unsigned int* num)
{
  *num = (unsigned int)pow(2, pfxlen);
  if (pfxlen == 32)
    *num = 0xFFFFFFFF;
  return 0;
}
