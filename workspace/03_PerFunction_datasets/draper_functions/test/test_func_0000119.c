e_cert_trust_add_peer_trust (CERTCertTrust *trust,
                             PRBool ssl,
                             PRBool email,
                             PRBool objSign)
{
	if (ssl)
		e_cert_trust_add_trust (&trust->sslFlags, CERTDB_TRUSTED);
	if (email)
		e_cert_trust_add_trust (&trust->emailFlags, CERTDB_TRUSTED);
	if (objSign)
		e_cert_trust_add_trust (&trust->objectSigningFlags, CERTDB_TRUSTED);
}
