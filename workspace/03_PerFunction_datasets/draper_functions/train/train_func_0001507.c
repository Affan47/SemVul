auth_totp_token_validate(Auth_token *token, char *otp_value, char *pin,
						 Token_pin_mode pin_mode, unsigned int time_step,
						 int clock_delta, unsigned int drift_window,
						 unsigned int ndigits, unsigned int base, int *driftp)
{

  if (token->mode & TOKEN_MODE_DISABLED) {
	log_msg((LOG_ERROR_LEVEL, "Token is disabled"));
	return(-1);
  }

  if ((pin == NULL && pin_mode != TOKEN_IGNORABLE_PIN)
	  || validate_pin(token, pin) == -1) {
	log_msg((LOG_ERROR_LEVEL, "PIN validation failed"));
	return(-1);
  }

  if (totp_validate(otp_value, token->digest_name, token->key,
					token->keylen, time_step, clock_delta,
					drift_window, ndigits, base, driftp) == -1)
	return(-1);

  return(0);
}
