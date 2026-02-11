capa_probe(int sock)

{
    int	ok;

    if (done_capa) {
	return PS_SUCCESS;
    }
#if defined(GSSAPI)
    has_gssapi = FALSE;
#endif
#if defined(KERBEROS_V4) || defined(KERBEROS_V5)
    has_kerberos = FALSE;
#endif
    has_cram = FALSE;
#ifdef OPIE_ENABLE
    has_otp = FALSE;
#endif
#ifdef NTLM_ENABLE
    has_ntlm = FALSE;
#endif

    ok = gen_transact(sock, "CAPA");
    if (ok == PS_SUCCESS)
    {
	char buffer[64];


	while ((ok = gen_recv(sock, buffer, sizeof(buffer))) == 0)
	{
	    if (DOTLINE(buffer))
		break;

#ifdef SSL_ENABLE
	    if (strstr(buffer, "STLS"))
		has_stls = TRUE;
#endif

#if defined(GSSAPI)
	    if (strstr(buffer, "GSSAPI"))
		has_gssapi = TRUE;
#endif

#if defined(KERBEROS_V4)
	    if (strstr(buffer, "KERBEROS_V4"))
		has_kerberos = TRUE;
#endif

#ifdef OPIE_ENABLE
	    if (strstr(buffer, "X-OTP"))
		has_otp = TRUE;
#endif

#ifdef NTLM_ENABLE
	    if (strstr(buffer, "NTLM"))
		has_ntlm = TRUE;
#endif

	    if (strstr(buffer, "CRAM-MD5"))
		has_cram = TRUE;
	}
    }
    done_capa = TRUE;
    return(ok);
}
