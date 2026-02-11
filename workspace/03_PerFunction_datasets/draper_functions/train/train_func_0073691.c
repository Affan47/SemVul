cmd_apdu (assuan_context_t ctx, char *line)
{
  ctrl_t ctrl = assuan_get_pointer (ctx);
  int rc;
  unsigned char *apdu;
  size_t apdulen;
  int with_atr;
  int handle_more;
  const char *s;
  size_t exlen;

  with_atr = has_option (line, "--atr");
  handle_more = has_option (line, "--more");

  if ((s=has_option_name (line, "--exlen")))
    {
      if (*s == '=')
        exlen = strtoul (s+1, NULL, 0);
      else
        exlen = 4096;
    }
  else
    exlen = 0;

  line = skip_options (line);

  if ( IS_LOCKED (ctrl) )
    return gpg_error (GPG_ERR_LOCKED);

  if ((rc = open_card (ctrl, NULL)))
    return rc;

  if (with_atr)
    {
      unsigned char *atr;
      size_t atrlen;
      char hexbuf[400];

      atr = apdu_get_atr (ctrl->reader_slot, &atrlen);
      if (!atr || atrlen > sizeof hexbuf - 2 )
        {
          rc = gpg_error (GPG_ERR_INV_CARD);
          goto leave;
        }
      bin2hex (atr, atrlen, hexbuf);
      xfree (atr);
      send_status_info (ctrl, "CARD-ATR", hexbuf, strlen (hexbuf), NULL, 0);
    }

  apdu = hex_to_buffer (line, &apdulen);
  if (!apdu)
    {
      rc = gpg_error_from_syserror ();
      goto leave;
    }
  if (apdulen)
    {
      unsigned char *result = NULL;
      size_t resultlen;

      rc = apdu_send_direct (ctrl->reader_slot, exlen,
                             apdu, apdulen, handle_more,
                             &result, &resultlen);
      if (rc)
        log_error ("apdu_send_direct failed: %s\n", gpg_strerror (rc));
      else
        {
          rc = assuan_send_data (ctx, result, resultlen);
          xfree (result);
        }
    }
  xfree (apdu);

 leave:
  TEST_CARD_REMOVAL (ctrl, rc);
  return rc;
}
