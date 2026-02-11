proposal_create_from_string(protocol_id_t protocol, const char *algs)
{
	private_proposal_t *this;
	enumerator_t *enumerator;
	bool failed = TRUE;
	char *alg;

	this = (private_proposal_t*)proposal_create(protocol, 0);


	enumerator = enumerator_create_token(algs, "-", " ");
	while (enumerator->enumerate(enumerator, &alg))
	{
		if (!add_string_algo(this, alg))
		{
			failed = TRUE;
			break;
		}
		failed = FALSE;
	}
	enumerator->destroy(enumerator);

	if (failed)
	{
		destroy(this);
		return NULL;
	}

	check_proposal(this);

	return &this->public;
}
