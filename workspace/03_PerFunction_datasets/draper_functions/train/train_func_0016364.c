e_cert_trust_has_trusted_ca (CERTCertTrust *trust,
                             PRBool checkSSL,
                             PRBool checkEmail,
                             PRBool checkObjSign)
{
	if (checkSSL && !(e_cert_trust_has_trust (
		trust->sslFlags, CERTDB_TRUSTED_CA) ||
		e_cert_trust_has_trust (
		trust->sslFlags, CERTDB_TRUSTED_CLIENT_CA)))
		return PR_FALSE;

	if (checkEmail && !(e_cert_trust_has_trust (
		trust->emailFlags, CERTDB_TRUSTED_CA) ||
		e_cert_trust_has_trust (
		trust->emailFlags, CERTDB_TRUSTED_CLIENT_CA)))
		return PR_FALSE;

	if (checkObjSign && !(e_cert_trust_has_trust (
		trust->objectSigningFlags, CERTDB_TRUSTED_CA) ||
		e_cert_trust_has_trust (
		trust->objectSigningFlags, CERTDB_TRUSTED_CLIENT_CA)))
		return PR_FALSE;

	return PR_TRUE;
}
