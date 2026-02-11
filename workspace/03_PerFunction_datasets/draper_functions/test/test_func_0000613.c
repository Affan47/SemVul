compress_algo_to_string(int algo)
{
  const char *s=NULL;

  switch(algo)
    {
    case COMPRESS_ALGO_NONE:
      s=_("Uncompressed");
      break;

    case COMPRESS_ALGO_ZIP:
      s="ZIP";
      break;

    case COMPRESS_ALGO_ZLIB:
      s="ZLIB";
      break;

#ifdef HAVE_BZIP2
    case COMPRESS_ALGO_BZIP2:
      s="BZIP2";
      break;
#endif
    }

  return s;
}
