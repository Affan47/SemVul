lineeditor_dkey_install
   ___P((lineeditor_input_decoder *decoder,
         char *cap,
         ___U8 event_no_escape,
         ___U8 event_with_escape,
         ___BOOL force_xterm),
        (decoder,
         cap,
         event_no_escape,
         event_with_escape,
         force_xterm)
lineeditor_input_decoder *decoder;
char *cap;
___U8 event_no_escape;
___U8 event_with_escape;
___BOOL force_xterm;)
{
  ___SCMOBJ e = ___FIX(___NO_ERR);
  char *seq;

#ifdef USE_TERMCAP_OR_TERMINFO

  if (!force_xterm)
    {
#ifdef USE_TERMCAP

      seq = tgetstr (cap, NULL);

#else

      seq = tigetstr (cap);

#endif
    }
  else

#endif

    seq = cap;

  if (seq != ___CAST(char*,-1) && seq != NULL)
    if ((e = lineeditor_input_decoder_add (decoder, seq, event_no_escape))
        != ___FIX(___NO_ERR) &&
        event_with_escape != (LINEEDITOR_EV_NONE|WITH_ESC_PREFIX))
      e = lineeditor_input_decoder_add (decoder, seq, event_with_escape);

  return e;
}
