e_cert_trust_copy (CERTCertTrust *trust,
                   CERTCertTrust *t)
{
	if (t)
		memcpy (trust, t, sizeof (CERTCertTrust));
	else
		memset (trust, 0, sizeof (CERTCertTrust));
}
