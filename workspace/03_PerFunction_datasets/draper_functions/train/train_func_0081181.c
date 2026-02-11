dump_raw(Trace *pTrace,unsigned int tbi, char *buf, int bufsize)
{
  if (!pTrace)
    return 0;

  int n = TraceType::dump_raw(pTrace, tbi,buf,bufsize);

  buf += n;
  bufsize -= n;

  RESET_TYPE r = (RESET_TYPE) (pTrace->get(tbi) & 0xff);

  int m = snprintf(buf, bufsize,
                   " %s Reset: %s",
                   (cpu ? cpu->name().c_str() : ""),
                   resetName(r));

  return m > 0 ? (m+n) : n;
}
