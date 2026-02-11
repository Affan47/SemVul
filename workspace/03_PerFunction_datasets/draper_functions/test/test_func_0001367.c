read_ef_tokeninfo (app_t app)
{
  gpg_error_t err;
  unsigned char *buffer = NULL;
  size_t buflen;
  const unsigned char *p;
  size_t n, objlen, hdrlen;
  int class, tag, constructed, ndef;
  unsigned long ul;

  err = select_and_read_binary (app->slot, 0x5032, "TokenInfo",
                                &buffer, &buflen);
  if (err)
    return err;

  p = buffer;
  n = buflen;

  err = parse_ber_header (&p, &n, &class, &tag, &constructed,
                          &ndef, &objlen, &hdrlen);
  if (!err && (objlen > n || tag != TAG_SEQUENCE))
    err = gpg_error (GPG_ERR_INV_OBJ);
  if (err)
    {
      log_error ("error parsing TokenInfo: %s\n", gpg_strerror (err));
      goto leave;
    }

  n = objlen;


  err = parse_ber_header (&p, &n, &class, &tag, &constructed,
                          &ndef, &objlen, &hdrlen);
  if (!err && (objlen > n || tag != TAG_INTEGER))
    err = gpg_error (GPG_ERR_INV_OBJ);
  if (err)
    goto leave;

  for (ul=0; objlen; objlen--)
    {
      ul <<= 8;
      ul |= (*p++) & 0xff;
      n--;
    }
  if (ul)
    {
      log_error ("invalid version %lu in TokenInfo\n", ul);
      err = gpg_error (GPG_ERR_INV_OBJ);
      goto leave;
    }


  err = parse_ber_header (&p, &n, &class, &tag, &constructed,
                          &ndef, &objlen, &hdrlen);
  if (!err && (objlen > n || tag != TAG_OCTET_STRING || !objlen))
    err = gpg_error (GPG_ERR_INV_OBJ);
  if (err)
    goto leave;

  xfree (app->app_local->serialno);
  app->app_local->serialno = xtrymalloc (objlen);
  if (!app->app_local->serialno)
    {
      err = gpg_error_from_syserror ();
      goto leave;
    }
  memcpy (app->app_local->serialno, p, objlen);
  app->app_local->serialnolen = objlen;
  log_printhex ("Serialnumber from EF(TokenInfo) is:", p, objlen);

 leave:
  xfree (buffer);
  return err;
}
