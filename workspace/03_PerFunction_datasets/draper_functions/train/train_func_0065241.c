real_to_target (buf, r, mode)
     long *buf;
     const REAL_VALUE_TYPE *r;
     enum machine_mode mode;
{
  const struct real_format *fmt;

  fmt = real_format_for_mode[mode - QFmode];
  if (fmt == NULL)
    abort ();

  return real_to_target_fmt (buf, r, fmt);
}
