build_trustchain(private_credential_manager_t *this,
									 certificate_t *subject, auth_cfg_t *auth)
{
	certificate_t *issuer, *current;
	auth_cfg_t *trustchain;
	int pathlen = 0;
	bool has_anchor;

	trustchain = auth_cfg_create();
	has_anchor = auth->get(auth, AUTH_RULE_CA_CERT) != NULL;
	current = subject->get_ref(subject);
	while (TRUE)
	{
		if (auth_contains_cacert(auth, current))
		{
			trustchain->add(trustchain, AUTH_RULE_CA_CERT, current);
			return trustchain;
		}
		if (subject == current)
		{
			trustchain->add(trustchain, AUTH_RULE_SUBJECT_CERT, current);
		}
		else
		{
			if (!has_anchor && issued_by(this, current, current, NULL))
			{
				trustchain->add(trustchain, AUTH_RULE_CA_CERT, current);
				return trustchain;
			}
			trustchain->add(trustchain, AUTH_RULE_IM_CERT, current);
		}
		if (pathlen++ > MAX_TRUST_PATH_LEN)
		{
			break;
		}
		issuer = get_issuer_cert(this, current, FALSE, NULL);
		if (!issuer)
		{
			if (!has_anchor)
			{
				return trustchain;
			}
			break;
		}
		if (has_anchor && issuer->equals(issuer, current))
		{
			issuer->destroy(issuer);
			break;
		}
		current = issuer;
	}
	trustchain->destroy(trustchain);
	return NULL;
}
