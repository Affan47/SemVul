fmtime(dsec, buf)
                  double dsec;
                  char *buf;
{
  long hrs, min, lsec;

  if( dsec <= 0 )
    {
      strcpy(buf, "0" );
      return;
    }
  lsec = fmod(dsec+0.5, 60L);
  hrs = dsec / 3600L;
  min = ((long)dsec / 60L) % 60L;
  if (hrs == 0)
     if (min == 0)
       sprintf(buf,"%6s%2ld"," ",lsec);
     else
       sprintf(buf,"%3s%2ld:%02ld"," ",min,lsec);
  else
    sprintf(buf,"%2ld:%02ld:%02ld",hrs,min,lsec);

}
