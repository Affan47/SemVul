double_to_str (char *out, size_t outlen, double value)
{
  const char *fmt;

  if (value < 1.0)
    fmt = "%.3f";
  else if (value < 100.0)
    fmt = "%.2f";
  else
    fmt = "%.1f";

  snprintf (out, outlen, fmt, value);
}
