config_get_defaultreferral() {
  slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();
  struct berval **refs;
  int nReferrals = 0;

  CFG_LOCK_READ(slapdFrontendConfig);

  for ( nReferrals = 0;
		slapdFrontendConfig->defaultreferral &&
		  slapdFrontendConfig->defaultreferral[nReferrals];
		nReferrals++)
	;

  refs = (struct berval **)
	slapi_ch_malloc( (nReferrals + 1) * sizeof(struct berval *) );


  refs [nReferrals--] = NULL;

  while ( nReferrals >= 0 ) {
	refs[nReferrals] = (struct berval *) slapi_ch_malloc( sizeof(struct berval) );
	refs[nReferrals]->bv_val =
	  config_copy_strval( slapdFrontendConfig->defaultreferral[nReferrals]->bv_val );
	refs[nReferrals]->bv_len =  slapdFrontendConfig->defaultreferral[nReferrals]->bv_len;
	nReferrals--;
  }
  CFG_UNLOCK_READ(slapdFrontendConfig);

  return refs;
}
