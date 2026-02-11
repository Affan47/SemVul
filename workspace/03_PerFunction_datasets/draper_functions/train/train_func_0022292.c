_trace_ulen_p (SQLULEN *p, int output)
{
  if (!p)
    trace_emit ("\t\t%-15.15s * 0x0\n", "SQLULEN");
  else if (output)
#ifdef _WIN64
    trace_emit ("\t\t%-15.15s * %p (%I64u)\n", "SQLULEN", p, (UINT64) *p);
#else
    trace_emit ("\t\t%-15.15s * %p (%lu)\n", "SQLULEN", p, (unsigned long) *p);
#endif
  else
    trace_emit ("\t\t%-15.15s * %p\n", "SQLULEN", p);
}
