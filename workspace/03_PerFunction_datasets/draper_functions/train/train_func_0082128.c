str2mac( u_int8_t * outmac , const char * s )
{
  size_t i;


  *outmac=hex2byte(s);
  ++outmac;
  s+=2;

  for (i=1; i<6; ++i )
    {
      s+=1;
      *outmac=hex2byte(s);
      ++outmac;
      s+=2;
    }

  return 0;
}
