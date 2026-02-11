ic_lookup_sts_authtype(char *authtype_str)
{

  if (strcaseeq(authtype_str, "passwd")
	  || strcaseeq(authtype_str, "password")
	  || strcaseeq(authtype_str, "UsernamePasswordCredential"))
	return(INFOCARD_AUTHTYPE_PASSWD);

  if (strcaseeq(authtype_str, "card")
	  || strcaseeq(authtype_str, "SelfIssuedCredential"))
	return(INFOCARD_AUTHTYPE_CARD);

  if (strcaseeq(authtype_str, "cert")
	  || strcaseeq(authtype_str, "X509V3Credential"))
	return(INFOCARD_AUTHTYPE_CERT);

  if (strcaseeq(authtype_str, "kerberos")
	  || strcaseeq(authtype_str, "KerberosV5Credential"))
	return(INFOCARD_AUTHTYPE_KERBEROS);

  return(INFOCARD_AUTHTYPE_NONE);
}
