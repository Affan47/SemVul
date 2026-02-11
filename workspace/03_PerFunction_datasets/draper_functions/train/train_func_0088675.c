_assuan_inquire_ext_cb (assuan_context_t ctx)
{
  gpg_error_t rc;
  unsigned char *line;
  int linelen;
  struct membuf *mb;
  unsigned char *p;

  line = (unsigned char *) ctx->inbound.line;
  linelen = ctx->inbound.linelen;
  mb = ctx->inquire_membuf;

  if (line[0] == 'C' && line[1] == 'A' && line[2] == 'N')
    {
      rc = _assuan_error (ctx, GPG_ERR_ASS_CANCELED);
      goto leave;
    }
  if (line[0] == 'E' && line[1] == 'N' && line[2] == 'D'
      && (!line[3] || line[3] == ' '))
    {
      rc = 0;
      goto leave;
    }

  if (line[0] != 'D' || line[1] != ' ' || mb == NULL)
    {
      rc = _assuan_error (ctx, GPG_ERR_ASS_UNEXPECTED_CMD);
      goto leave;
    }

  if (linelen < 3)
    return 0;
  line += 2;
  linelen -= 2;

  p = line;
  while (linelen)
    {
      for (;linelen && *p != '%'; linelen--, p++)
	;
      put_membuf (ctx, mb, line, p-line);
      if (linelen > 2)
	{
	  unsigned char tmp[1];
	  p++;
	  *tmp = xtoi_2 (p);
	  p += 2;
	  linelen -= 3;
	  put_membuf (ctx, mb, tmp, 1);
	}
      line = p;
    }
  if (mb->too_large)
    {
      rc = _assuan_error (ctx, GPG_ERR_ASS_TOO_MUCH_DATA);
      goto leave;
    }

  return 0;

 leave:
  {
    size_t buf_len = 0;
    unsigned char *buf = NULL;

    if (mb)
      {
	buf = get_membuf (ctx, mb, &buf_len);
	if (!buf)
	  rc = _assuan_error (ctx, gpg_err_code_from_syserror ());
	free_membuf (ctx, mb);
	free (mb);
	ctx->inquire_membuf = NULL;
      }
    ctx->in_inquire = 0;
    rc = (ctx->inquire_cb) (ctx->inquire_cb_data, rc, buf, buf_len);
  }
  return rc;
}
