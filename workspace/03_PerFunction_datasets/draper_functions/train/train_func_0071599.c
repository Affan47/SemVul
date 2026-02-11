cmd_serialno (assuan_context_t ctx, char *line)
{
  ctrl_t ctrl = assuan_get_pointer (ctx);
  int rc = 0;
  char *serial_and_stamp;
  char *serial;
  time_t stamp;
  int retries = 0;


 retry:
  if (ctrl->server_local->card_removed)
    {
      if ( IS_LOCKED (ctrl) )
        return gpg_error (GPG_ERR_LOCKED);
      do_reset (ctrl, 1);
    }

  if ((rc = open_card (ctrl, *line? line:NULL)))
    {

      if (gpg_err_code (rc) == GPG_ERR_CARD_RESET && retries++ < 1)
        goto retry;
      return rc;
    }

  rc = app_get_serial_and_stamp (ctrl->app_ctx, &serial, &stamp);
  if (rc)
    return rc;

  rc = estream_asprintf (&serial_and_stamp, "%s %lu",
                         serial, (unsigned long)stamp);
  xfree (serial);
  if (rc < 0)
    return out_of_core ();
  rc = 0;
  assuan_write_status (ctx, "SERIALNO", serial_and_stamp);
  xfree (serial_and_stamp);
  return 0;
}
