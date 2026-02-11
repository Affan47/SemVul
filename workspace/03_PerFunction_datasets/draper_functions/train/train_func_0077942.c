authdes_refresh (AUTH *auth)
{
  netobj pkey;
  struct ad_private *ad = AUTH_PRIVATE (auth);
  struct authdes_cred *cred = &ad->ad_cred;

  if (ad->ad_dosync && !synchronize (&ad->ad_syncaddr, &ad->ad_timediff))
    {


      ad->ad_timediff.tv_sec = ad->ad_timediff.tv_usec = 0;
      debug ("authdes_refresh: unable to synchronize with server");
    }
  ad->ad_xkey = auth->ah_key;
  pkey.n_bytes = (char *) (ad->ad_pkey);
  pkey.n_len = strlen ((char *) ad->ad_pkey) + 1;
  if (key_encryptsession_pk (ad->ad_servername, &pkey, &ad->ad_xkey) < 0)
    {
      debug ("authdes_create: unable to encrypt conversation key");
      return FALSE;
    }
  cred->adc_fullname.key = ad->ad_xkey;
  cred->adc_namekind = ADN_FULLNAME;
  cred->adc_fullname.name = ad->ad_fullname;
  return TRUE;
}
