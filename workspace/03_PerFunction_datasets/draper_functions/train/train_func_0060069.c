vwarning (Loc loc, const char *format, va_list ap)
{
  if (global.params.warnings && !global.gag)
    {
      location_t location = get_linemap (loc);
      char *msg;

      if (vasprintf (&msg, format, ap) >= 0 && msg != NULL)
	warning_at (location, 0, "%s", msg);


      if (global.params.warnings == 1)
	global.warnings++;
    }
}
