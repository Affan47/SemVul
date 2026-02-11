divert_pksign (ctrl_t ctrl,
               const unsigned char *digest, size_t digestlen, int algo,
               const unsigned char *shadow_info, unsigned char **r_sig)
{
  int rc;
  char *kid;
  size_t siglen;
  unsigned char *sigval = NULL;

  rc = ask_for_card (ctrl, shadow_info, &kid);
  if (rc)
    return rc;

  if (algo == MD_USER_TLS_MD5SHA1)
    {
      int save = ctrl->use_auth_call;
      ctrl->use_auth_call = 1;
      rc = agent_card_pksign (ctrl, kid, getpin_cb, ctrl,
                              digest, digestlen, &sigval, &siglen);
      ctrl->use_auth_call = save;
    }
  else
    {
      unsigned char *data;
      size_t ndata;

      rc = encode_md_for_card (digest, digestlen, algo, &data, &ndata);
      if (!rc)
        {
          rc = agent_card_pksign (ctrl, kid, getpin_cb, ctrl,
                                  data, ndata, &sigval, &siglen);
          xfree (data);
        }
    }

  if (!rc)
    *r_sig = sigval;

  xfree (kid);

  return rc;
}
