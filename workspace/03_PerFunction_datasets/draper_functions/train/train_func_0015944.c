authdes_validate (AUTH *auth, struct opaque_auth *rverf)
{
  struct ad_private *ad = AUTH_PRIVATE (auth);
  struct authdes_verf verf;
  int status;
  register uint32_t *ixdr;

  if (rverf->oa_length != (2 + 1) * BYTES_PER_XDR_UNIT)
    return FALSE;

  ixdr = (uint32_t *) rverf->oa_base;
  verf.adv_xtimestamp.key.high = *ixdr++;
  verf.adv_xtimestamp.key.low = *ixdr++;
  verf.adv_int_u = *ixdr++;


  status = ecb_crypt ((char *) &auth->ah_key, (char *) &verf.adv_xtimestamp,
		      sizeof (des_block), DES_DECRYPT | DES_HW);

  if (DES_FAILED (status))
    {
      debug ("authdes_validate: DES decryption failure");
      return FALSE;
    }


  ixdr = (uint32_t *) verf.adv_xtimestamp.c;
  verf.adv_timestamp.tv_sec = IXDR_GET_U_INT32 (ixdr) + 1;
  verf.adv_timestamp.tv_usec = IXDR_GET_U_INT32 (ixdr);


  if (memcmp ((char *) &ad->ad_timestamp, (char *) &verf.adv_timestamp,
	      sizeof (struct rpc_timeval)) != 0)
    {
      debug ("authdes_validate: verifier mismatch\n");
      return FALSE;
    }


  ad->ad_nickname = verf.adv_nickname;
  ad->ad_cred.adc_namekind = ADN_NICKNAME;
  return TRUE;
}
