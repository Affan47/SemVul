b64enc_start (struct b64state *state, FILE *fp, const char *title)
{
  memset (state, 0, sizeof *state);
  state->fp = fp;
  if (title && !*title)
    state->flags |= B64ENC_NO_LINEFEEDS;
  else if (title)
    {
      if (!strncmp (title, "PGP ", 4))
        {
          state->flags |= B64ENC_USE_PGPCRC;
          state->crc = CRCINIT;
        }
      state->title = xtrystrdup (title);
      if (!state->title)
        return gpg_error_from_syserror ();
    }
  return 0;
}
