dump_raw(Trace *pTrace, unsigned int tbi, char *buf, int bufsize)
{
  if (!pTrace)
    return 0;

  int n = TraceType::dump_raw(pTrace, tbi,buf,bufsize);

  buf += n;
  bufsize -= n;

  unsigned int tv = pTrace->get(tbi);
  unsigned int address = (tv >> 8) & 0xfff;

  Register *reg = cpu->rma.get_register(address);
  int m = snprintf(buf, bufsize,
                   "  Reg Read:  %s(0x%04X) was 0x%0X",
                   (reg ? reg->name().c_str() : ""), address,
                   tv & 0xff);

  if(m>0)
    n += m;

  return n;

}
