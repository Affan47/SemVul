toNative(const EscapeMode escape) const
{
  GP<GStringRep> retval;
  if(data[0])
  {
    const size_t length=strlen(data);
    const unsigned char * const eptr=(const unsigned char *)(data+length);
    unsigned char *buf;
    GPBuffer<unsigned char> gbuf(buf,12*length+12);
    unsigned char *r=buf;
    mbstate_t ps;
    memset(&ps,0,sizeof(mbstate_t));
    for(const unsigned char *s=(const unsigned char *)data;(s<eptr)&& *s;)
      {
        const unsigned char * const s0 = s;
        const uint32_t w0=UTF8toUCS4(s,eptr);
        if (s == s0)
          {
            s += 1;
            *r++ = '?';
          }
        else
          {
            const unsigned char * const r0 = r;
            r=UCS4toNative(w0,r,&ps);
            if(r == r0)
              {
                if (escape == IS_ESCAPED)
                  {
                    sprintf((char *)r,"&#%lu;",(unsigned long)w0);
                    r += strlen((char *)r);
                  }
                else
                  {
                    *r++ = '?';
                  }
              }
          }
      }
    r[0]=0;
    retval = NATIVE_CREATE( (const char *)buf );
  }
  else
  {
    retval = NATIVE_CREATE( (unsigned int)0 );
  }
  return retval;
}
