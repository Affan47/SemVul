handle_iconv_error (const char *to, const char *from, int use_fallback)
{
  if (errno == EINVAL)
    {
      static int shown1, shown2;
      int x;

      if (to && !strcmp (to, "utf-8"))
        {
          x = shown1;
          shown1 = 1;
        }
      else
        {
          x = shown2;
          shown2 = 1;
        }

      if (!x)
        log_info (_("conversion from `%s' to `%s' not available\n"),
                  from, to);
    }
  else
    {
      static int shown;

      if (!shown)
        log_info (_("iconv_open failed: %s\n"), strerror (errno));
      shown = 1;
    }

  if (use_fallback)
    {


      active_charset_name = "iso-8859-1";
      no_translation = 0;
      active_charset = NULL;
      use_iconv = 0;
    }
}
