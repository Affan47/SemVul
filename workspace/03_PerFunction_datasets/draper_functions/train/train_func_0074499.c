UtcShiftInterval(time_t t, char *out, int outSz)


{
  char buf[CF_MAXVARSIZE];
  int hr = 0, fromHr = 0, toHr = 0;

  cf_strtimestamp_utc(t,buf);

  sscanf(buf+11,"%d", &hr);
  buf[11] = '\0';

  if(hr < 6)
    {
      fromHr = 0;
      toHr = 6;
    }
  else if(hr < 12)
    {
      fromHr = 6;
      toHr = 12;
    }
  else if(hr < 18)
    {
      fromHr = 12;
      toHr = 18;
    }
  else
    {
      fromHr = 18;
      toHr = 24;
    }

  snprintf(out, outSz, "%s %02d-%02d", buf, fromHr, toHr);
}
