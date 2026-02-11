assuan_transact (assuan_context_t ctx,
                 const char *command,
                 gpg_error_t (*data_cb)(void *, const void *, size_t),
                 void *data_cb_arg,
                 gpg_error_t (*inquire_cb)(void*, const char *),
                 void *inquire_cb_arg,
                 gpg_error_t (*status_cb)(void*, const char *),
                 void *status_cb_arg)
{
  gpg_error_t rc;
  assuan_response_t response;
  int off;
  char *line;
  int linelen;

  rc = assuan_write_line (ctx, command);
  if (rc)
    return rc;

  if (*command == '#' || !*command)
    return 0;

 again:
  rc = _assuan_read_from_server (ctx, &response, &off);
  if (rc)
    return rc;

  line = ctx->inbound.line + off;
  linelen = ctx->inbound.linelen - off;

  if (response == ASSUAN_RESPONSE_ERROR)
    rc = atoi (line);
  else if (response == ASSUAN_RESPONSE_DATA)
    {
      if (!data_cb)
        rc = _assuan_error (ctx, GPG_ERR_ASS_NO_DATA_CB);
      else
        {
          rc = data_cb (data_cb_arg, line, linelen);
          if (!rc)
            goto again;
        }
    }
  else if (response == ASSUAN_RESPONSE_INQUIRE)
    {
      if (!inquire_cb)
        {
          assuan_write_line (ctx, "END");
          _assuan_read_from_server (ctx, &response, &off);
          rc = _assuan_error (ctx, GPG_ERR_ASS_NO_INQUIRE_CB);
        }
      else
        {
          rc = inquire_cb (inquire_cb_arg, line);
          if (!rc)
            rc = assuan_send_data (ctx, NULL, 0);
          if (!rc)
            goto again;
        }
    }
  else if (response == ASSUAN_RESPONSE_STATUS)
    {
      if (status_cb)
        rc = status_cb (status_cb_arg, line);
      if (!rc)
        goto again;
    }
  else if (response == ASSUAN_RESPONSE_END)
    {
      if (!data_cb)
        rc = _assuan_error (ctx, GPG_ERR_ASS_NO_DATA_CB);
      else
        {
          rc = data_cb (data_cb_arg, NULL, 0);
          if (!rc)
            goto again;
        }
    }

  return rc;
}
