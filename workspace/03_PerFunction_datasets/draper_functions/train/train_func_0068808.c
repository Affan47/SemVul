ChapMS2(u_char *rchallenge, u_char *PeerChallenge,
	char *user, char *secret, int secret_len, unsigned char *response,
	u_char authResponse[], int authenticator)
{

    u_char *p = &response[MS_CHAP2_PEER_CHALLENGE];
    int i;

    BZERO(response, MS_CHAP2_RESPONSE_LEN);


    if (!PeerChallenge)
	for (i = 0; i < MS_CHAP2_PEER_CHAL_LEN; i++)
	    *p++ = (u_char) (drand48() * 0xff);
    else
	BCOPY(PeerChallenge, &response[MS_CHAP2_PEER_CHALLENGE],
	      MS_CHAP2_PEER_CHAL_LEN);


    ChapMS2_NT(rchallenge, &response[MS_CHAP2_PEER_CHALLENGE], user,
	       secret, secret_len, &response[MS_CHAP2_NTRESP]);


    GenerateAuthenticatorResponsePlain(secret, secret_len,
				       &response[MS_CHAP2_NTRESP],
				       &response[MS_CHAP2_PEER_CHALLENGE],
				       rchallenge, user, authResponse);

#ifdef MPPE
    SetMasterKeys(secret, secret_len,
		  &response[MS_CHAP2_NTRESP], authenticator);
#endif
}
