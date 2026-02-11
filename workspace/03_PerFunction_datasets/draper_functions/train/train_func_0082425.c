getValidUCS4(const char *&source) const
{
  uint32_t retval=0;
  int n=(int)((size_t)size+(size_t)data-(size_t)source);
  if(source && (n > 0))
  {
    mbstate_t ps;

    memset(&ps,0,sizeof(mbstate_t));
    wchar_t wt;
    const int len=mbrtowc(&wt,source,n,&ps);
    if(len>=0)
    {
      if(sizeof(wchar_t) == sizeof(uint16_t))
      {
        source+=len;
        uint16_t s[2];
        s[0]=(uint16_t)wt;
        if(UTF16toUCS4(retval,s,s+1)<=0)
        {
          if((n-=len)>0)
          {
            const int len=mbrtowc(&wt,source,n,&ps);
            if(len>=0)
            {
              s[1]=(uint16_t)wt;
              uint32_t w;
              if(UTF16toUCS4(w,s,s+2)>0)
              {
                source+=len;
                retval=w;
              }
            }
          }
        }
      }else
      {
        retval=(uint32_t)wt;
        source++;
      }
    }else
    {
      source++;
    }
  }
  return retval;
}
