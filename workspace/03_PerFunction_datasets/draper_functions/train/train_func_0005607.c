agent_card_pkdecrypt (ctrl_t ctrl,
                      const char *keyid,
                      int (*getpin_cb)(void *, const char *, char*, size_t),
                      void *getpin_cb_arg,
                      const unsigned char *indata, size_t indatalen,
                      char **r_buf, size_t *r_buflen)
{
  int rc, i;
  char *p, line[ASSUAN_LINELENGTH];
  membuf_t data;
  struct inq_needpin_s inqparm;
  size_t len;

  *r_buf = NULL;
  rc = start_scd (ctrl);
  if (rc)
    return rc;


  if (indatalen*2 + 50 > DIM(line))
    return unlock_scd (ctrl, gpg_error (GPG_ERR_GENERAL));

  sprintf (line, "SETDATA ");
  p = line + strlen (line);
  for (i=0; i < indatalen ; i++, p += 2 )
    sprintf (p, "%02X", indata[i]);
  rc = assuan_transact (ctrl->scd_local->ctx, line,
                        NULL, NULL, NULL, NULL, NULL, NULL);
  if (rc)
    return unlock_scd (ctrl, rc);

  init_membuf (&data, 1024);
  inqparm.ctx = ctrl->scd_local->ctx;
  inqparm.getpin_cb = getpin_cb;
  inqparm.getpin_cb_arg = getpin_cb_arg;
  inqparm.passthru = 0;
  snprintf (line, DIM(line)-1, "PKDECRYPT %s", keyid);
  line[DIM(line)-1] = 0;
  rc = assuan_transact (ctrl->scd_local->ctx, line,
                        membuf_data_cb, &data,
                        inq_needpin, &inqparm,
                        NULL, NULL);
  if (rc)
    {
      xfree (get_membuf (&data, &len));
      return unlock_scd (ctrl, rc);
    }
  *r_buf = get_membuf (&data, r_buflen);
  if (!*r_buf)
    return unlock_scd (ctrl, gpg_error (GPG_ERR_ENOMEM));

  return unlock_scd (ctrl, 0);
}
