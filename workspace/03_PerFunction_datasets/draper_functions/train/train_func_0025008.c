space (argp_fmtstream_t stream, size_t ensure)
{
  if (__argp_fmtstream_point (stream) + ensure
      >= __argp_fmtstream_rmargin (stream))
    __argp_fmtstream_putc (stream, '\n');
  else
    __argp_fmtstream_putc (stream, ' ');
}
