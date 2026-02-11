handle_close (unsigned char *argbuf, size_t arglen)
{
  (void)argbuf;
  (void)arglen;

  if (!driver_is_open)
    {
      fprintf (stderr, PGM ": PC/SC has not yet been opened\n");
      request_failed (-1);
      return;
    }

  free (current_rdrname);
  current_rdrname = NULL;
  pcsc_release_context (pcsc_context);
  pcsc_card = 0;
  pcsc_protocol = 0;

  request_succeeded (NULL, 0);
}
