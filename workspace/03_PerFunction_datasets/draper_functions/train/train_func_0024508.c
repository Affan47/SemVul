generic_phoenix_xor(unsigned int *value, const unsigned int lng)
{
  unsigned int i;
  for(i=0;(i<lng)&&(value[i]!=VAL_STOP);i++)
    value[i]=(value[i] ^ 0xF0) + i;
}
