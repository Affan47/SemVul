SetMagickPrecision(const int precision)
{
#define MagickPrecision  6

  static int
    magick_precision = 0;

  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  if (precision > 0)
    magick_precision=precision;
  if ((precision < 0) || (magick_precision == 0))
    {
      char
        *limit;


      magick_precision = MagickPrecision;
      limit=GetEnvironmentValue("MAGICK_PRECISION");
      if (limit == (char *) NULL)
        limit=GetPolicyValue("precision");
      if (limit != (char *) NULL)
        {
          magick_precision=StringToInteger(limit);
          limit=DestroyString(limit);
        }
    }
  return(magick_precision);
}
