encode_s2k_iterations(int iterations)
{
  unsigned char c=0,result;
  unsigned int count;

  if(iterations<=1024)
    return 0;

  if(iterations>=65011712)
    return 255;


  for(count=iterations>>6;count>=32;count>>=1)
    c++;

  result=(c<<4)|(count-16);

  if(S2K_DECODE_COUNT(result)<iterations)
    result++;

  return result;
}
