hotp_validate(char *otp_value, unsigned char *key, unsigned int klen,
			  unsigned char *counter, unsigned int clen, unsigned int ndigits,
			  unsigned int base, unsigned int window)
{
  int i;
  char *hval;
  unsigned char *saved_counter;


  saved_counter = token_copy_counter(counter, NULL);
  token_inc_counter(counter);

  log_msg((LOG_TRACE_LEVEL, "Checking for expected HOTP match"));
  hval = auth_hotp_value(key, klen, counter, clen, ndigits, base);
  if (streq(otp_value, hval)) {
	log_msg((LOG_DEBUG_LEVEL, "HOTP matched, counter=%s",
			 token_format_counter(counter)));
	return(0);
  }
  log_msg((LOG_TRACE_LEVEL, "HOTP=\"%s\", counter=%s",
		   hval, token_format_counter(counter)));


  log_msg((LOG_TRACE_LEVEL, "Scanning forward for HOTP match"));
  for (i = 1; i <= window; i++) {
	token_inc_counter(counter);
	hval = auth_hotp_value(key, klen, counter, clen, ndigits, base);
	if (streq(otp_value, hval)) {
	  log_msg((LOG_DEBUG_LEVEL, "HOTP matched, counter=%s",
			   token_format_counter(counter)));
	  return(0);
	}
	log_msg((LOG_TRACE_LEVEL, "HOTP=\"%s\", counter=%s",
			 hval, token_format_counter(counter)));
  }

  log_msg((LOG_DEBUG_LEVEL, "HOTP did not match"));
  return(-1);
}
