auth_get_cram(const char *authtype, char *authdata,
		  struct cram_callback_info *craminfo)
{
int	i;
int	challenge_l;
int	response_l;

	if (strncmp(authtype, "cram-", 5) ||
		(craminfo->challenge=strtok(authdata, "\n")) == 0 ||
		(craminfo->response=strtok(0, "\n")) == 0)
	{
		DPRINTF("Unsupported authentication type: %s", authtype);
		errno=EPERM;
		return (-1);
	}

	for (i=0; hmac_list[i]; i++)
		if (strcmp(hmac_list[i]->hh_name, authtype+5) == 0)
			break;

	DPRINTF("cram: challenge=%s, response=%s", craminfo->challenge,
		craminfo->response);

	if (hmac_list[i] == 0
		|| (challenge_l=authsasl_frombase64(craminfo->challenge)) < 0
		|| (response_l=authsasl_frombase64(craminfo->response)) < 0)
	{
		DPRINTF("cram: invalid base64 encoding, or unknown method: %s",
			authtype);
		errno=EACCES;
		return (-1);
	}
	craminfo->h=hmac_list[i];

	for (i=response_l; i > 0; )
	{
		if (craminfo->response[i-1] == ' ')
			break;
		--i;
	}

	if (i == 0)
	{
		DPRINTF("cram: invalid base64 encoding");
		errno=EACCES;
		return (-1);
	}
	craminfo->response[i-1]=0;
	craminfo->user = craminfo->response;
	craminfo->response += i;
	response_l -= i;


	craminfo->challenge[challenge_l]=0;
	craminfo->response[response_l]=0;


	DPRINTF("cram: decoded challenge/response, username '%s'",
		craminfo->user);
	return (0);
}
