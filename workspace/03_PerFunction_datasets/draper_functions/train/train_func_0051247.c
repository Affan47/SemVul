UTF16BEtoUCS4(unsigned char const *&s,void const * const eptr)
{
  uint32_t U=0;
  unsigned char const * const r=s+2;
  if(r <= eptr)
    {
      uint32_t const C1MSB=s[0];
      if((C1MSB<0xD8)||(C1MSB>0xDF))
        {
          if((U=((C1MSB<<8)|((uint32_t)s[1]))))
            {
              s=r;
            }
        }
      else if(C1MSB<=0xDB)
        {
          unsigned char const * const rr=r+2;
          if(rr <= eptr)
            {
              uint32_t const C2MSB=s[2];
              if((C2MSB>=0xDC)||(C2MSB<=0xDF))
                {
                  U=0x10000+((uint32_t)s[1]<<10)+(uint32_t)s[3]
                    +(((C1MSB<<18)|(C2MSB<<8))&0xc0300);
                  s=rr;
                }
              else
                {
                  U=(unsigned int)(-1)-((C1MSB<<8)|((uint32_t)s[1]));
                  s=r;
                }
            }
        }
    }
  return U;
}
