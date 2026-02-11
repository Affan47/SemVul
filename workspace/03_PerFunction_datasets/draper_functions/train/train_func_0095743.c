totp_validate(char *otp_value, char *digest_name, unsigned char *key,
			  unsigned int keylen, unsigned int time_step,
			  int clock_delta, unsigned int drift_window, unsigned int ndigits,
			  unsigned int base, int *driftp)
{
  int i;
  char *hval;
  time_t now;

  time(&now);


  now += clock_delta;


  hval = auth_totp_value(digest_name, key, keylen,
						 &now, time_step, 0, ndigits, base, NULL);

  if (streq(otp_value, hval)) {
	if (driftp != NULL)
	  *driftp = 0;
	log_msg((LOG_TRACE_LEVEL, "Exact TOTP match"));
	return(0);
  }

  for (i = 1; i <= drift_window; i++) {
	hval = auth_totp_value(digest_name, key, keylen, &now, time_step,
						   i * time_step, ndigits, base, NULL);
	if (streq(otp_value, hval)) {
	  if (driftp != NULL)
		*driftp = i;
	  log_msg((LOG_TRACE_LEVEL, "TOTP matched in +%d window", i));
	  return(0);
	}
	hval = auth_totp_value(digest_name, key, keylen, &now, time_step,
						   -i * time_step, ndigits, base, NULL);
	if (streq(otp_value, hval)) {
	  if (driftp != NULL)
		*driftp = -i;
	  log_msg((LOG_TRACE_LEVEL, "TOTP matched in -%d window", i));
	  return(0);
	}
  }

  log_msg((LOG_DEBUG_LEVEL, "TOTP failed to match within %d windows",
		   drift_window));
  return(-1);
}
