_gsasl_openid20_server_step (Gsasl_session * sctx,
			     void *mech_data,
			     const char *input, size_t input_len,
			     char **output, size_t * output_len)
{
  struct openid20_server_state *state = mech_data;
  int res = GSASL_MECHANISM_CALLED_TOO_MANY_TIMES;

  *output_len = 0;
  *output = NULL;

  switch (state->step)
    {
    case 0:
      {
	const char *p;
	char *authzid;
	size_t headerlen;

	if (input_len == 0)
	  return GSASL_NEEDS_MORE;

	res = _gsasl_parse_gs2_header (input, input_len,
				       &authzid, &headerlen);
	if (res != GSASL_OK)
	  return res;

	if (authzid)
	  {
	    gsasl_property_set (sctx, GSASL_AUTHZID, authzid);
	    free (authzid);
	  }

	input += headerlen;
	input_len -= headerlen;

	gsasl_property_set_raw (sctx, GSASL_AUTHID, input, input_len);

	p = gsasl_property_get (sctx, GSASL_OPENID20_REDIRECT_URL);
	if (!p || !*p)
	  return GSASL_NO_OPENID20_REDIRECT_URL;

	*output_len = strlen (p);
	*output = malloc (*output_len);
	if (!*output)
	  return GSASL_MALLOC_ERROR;

	memcpy (*output, p, *output_len);

	res = GSASL_NEEDS_MORE;
	state->step++;
	break;
      }

    case 1:
      {
	const char *outcome_data;

	if (!(input_len == 1 && *input == '='))
	  return GSASL_MECHANISM_PARSE_ERROR;

	res = gsasl_callback (NULL, sctx, GSASL_VALIDATE_OPENID20);
	if (res != GSASL_OK)
	  {
	    *output = strdup ("openid.error=fail");
	    if (!*output)
	      return GSASL_MALLOC_ERROR;
	    *output_len = strlen (*output);


	    state->allow_error_step = 1;
	    state->step++;
	    return GSASL_NEEDS_MORE;
	  }

	outcome_data = gsasl_property_get (sctx, GSASL_OPENID20_OUTCOME_DATA);
	if (outcome_data)
	  {
	    *output = strdup (outcome_data);
	    if (!*output)
	      return GSASL_MALLOC_ERROR;
	    *output_len = strlen (*output);
	  }
	else
	  {
	    *output = NULL;
	    *output_len = 0;
	  }

	res = GSASL_OK;
	state->step++;
      }
      break;

    case 2:
      {


	if (!state->allow_error_step)
	  return GSASL_MECHANISM_CALLED_TOO_MANY_TIMES;

	if (!(input_len == 1 && *input == '='))
	  return GSASL_MECHANISM_PARSE_ERROR;

	res = GSASL_AUTHENTICATION_ERROR;
	state->step++;
      }
      break;

    default:
      break;
    }

  return res;
}
