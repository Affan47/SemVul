is_gzip_supported(void)
{
  if (gzip_is_supported >= 0)
    return gzip_is_supported;

  if (!strcmpstart(ZLIB_VERSION, "0.") ||
      !strcmpstart(ZLIB_VERSION, "1.0") ||
      !strcmpstart(ZLIB_VERSION, "1.1"))
    gzip_is_supported = 0;
  else
    gzip_is_supported = 1;

  return gzip_is_supported;
}
