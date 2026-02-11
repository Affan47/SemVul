rc_check_reply (AUTH_HDR *auth, int bufferlen, char *secret,
			   unsigned char *vector, unsigned char seq_nbr)
{
	int             secretlen;
	int             totallen;
	unsigned char   calc_digest[AUTH_VECTOR_LEN];
	unsigned char   reply_digest[AUTH_VECTOR_LEN];

	totallen = ntohs (auth->length);

	secretlen = strlen (secret);


	if ((totallen < 20) || (totallen > 4096))
	{
		error("rc_check_reply: received RADIUS server response with invalid length");
		return (BADRESP_RC);
	}


	if ((totallen + secretlen) > bufferlen)
	{
		error("rc_check_reply: not enough buffer space to verify RADIUS server response");
		return (BADRESP_RC);
	}

	if (auth->id != seq_nbr)
	{
		error("rc_check_reply: received non-matching id in RADIUS server response");
		return (BADRESP_RC);
	}


	memcpy ((char *) reply_digest, (char *) auth->vector, AUTH_VECTOR_LEN);
	memcpy ((char *) auth->vector, (char *) vector, AUTH_VECTOR_LEN);
	memcpy ((char *) auth + totallen, secret, secretlen);
	rc_md5_calc (calc_digest, (char *) auth, totallen + secretlen);

#ifdef DIGEST_DEBUG
	{
		int i;

		fputs("reply_digest: ", stderr);
		for (i = 0; i < AUTH_VECTOR_LEN; i++)
		{
			fprintf(stderr,"%.2x ", (int) reply_digest[i]);
		}
		fputs("\ncalc_digest:  ", stderr);
		for (i = 0; i < AUTH_VECTOR_LEN; i++)
		{
			fprintf(stderr,"%.2x ", (int) calc_digest[i]);
		}
		fputs("\n", stderr);
	}
#endif

	if (memcmp ((char *) reply_digest, (char *) calc_digest,
		    AUTH_VECTOR_LEN) != 0)
	{
#ifdef RADIUS_116


		if (auth->code == PW_ACCOUNTING_RESPONSE)
			return (OK_RC);
#endif
		error("rc_check_reply: received invalid reply digest from RADIUS server");
		return (BADRESP_RC);
	}

	return (OK_RC);

}
