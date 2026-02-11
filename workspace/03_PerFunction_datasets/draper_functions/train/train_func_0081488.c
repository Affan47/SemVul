_dl_signal_cerror (int errcode, const char *objname, const char *occation,
		   const char *errstring)
{
  if (__builtin_expect (GLRO_dl_debug_mask
			& ~(DL_DEBUG_STATISTICS|DL_DEBUG_PRELINK), 0))
    _dl_debug_printf ("%s: error: %s: %s (%s)\n", objname, occation,
		      errstring, receiver ? "continued" : "fatal");

  if (receiver)
    {


      (*receiver) (errcode, objname, errstring);
    }
  else
    _dl_signal_error (errcode, objname, occation, errstring);
}
