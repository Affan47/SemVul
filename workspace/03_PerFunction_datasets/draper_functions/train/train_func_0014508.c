do_decipher (app_t app, const char *keyidstr,
             gpg_error_t (*pincb)(void*, const char *, char **),
             void *pincb_arg,
             const void *indata, size_t indatalen,
             unsigned char **outdata, size_t *outdatalen )
{
  int rc, i;
  int is_sigg = 0;
  int fid;
  int kid;

  if (!keyidstr || !*keyidstr || !indatalen)
    return gpg_error (GPG_ERR_INV_VALUE);


  if (!strncmp (keyidstr, "NKS-NKS3.", 9) )
    ;
  else if (!strncmp (keyidstr, "NKS-DF01.", 9) )
    ;
  else if (!strncmp (keyidstr, "NKS-SIGG.", 9) )
    is_sigg = 1;
  else
    return gpg_error (GPG_ERR_INV_ID);
  keyidstr += 9;

  rc = switch_application (app, is_sigg);
  if (rc)
    return rc;

  if (!hexdigitp (keyidstr) || !hexdigitp (keyidstr+1)
      || !hexdigitp (keyidstr+2) || !hexdigitp (keyidstr+3)
      || keyidstr[4])
    return gpg_error (GPG_ERR_INV_ID);
  fid = xtoi_4 (keyidstr);
  for (i=0; filelist[i].fid; i++)
    if (filelist[i].iskeypair && filelist[i].fid == fid)
      break;
  if (!filelist[i].fid)
    return gpg_error (GPG_ERR_NOT_FOUND);
  if (!filelist[i].isenckey)
    return gpg_error (GPG_ERR_INV_ID);
  kid = filelist[i].kid;

  if (app->app_local->nks_version > 2)
    {
      unsigned char mse[6];
      mse[0] = 0x80;
      mse[1] = 1;
      mse[2] = 0x0a;
      mse[3] = 0x84;
      mse[4] = 1;
      mse[5] = kid;
      rc = iso7816_manage_security_env (app->slot, 0x41, 0xB8,
                                        mse, sizeof mse);
    }
  else
    {
      static const unsigned char mse[] =
        {
          0x80, 1, 0x10,
          0x84, 1, 0x81
        };
      rc = iso7816_manage_security_env (app->slot, 0xC1, 0xB8,
                                        mse, sizeof mse);

    }

  if (!rc)
    rc = verify_pin (app, 0, NULL, pincb, pincb_arg);


  if (!rc)
    rc = iso7816_decipher (app->slot, app->app_local->nks_version > 2? 1:0,
                           indata, indatalen, 0, 0x81,
                           outdata, outdatalen);
  return rc;
}
