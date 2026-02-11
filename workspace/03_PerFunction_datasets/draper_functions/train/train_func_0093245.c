skipped_auth(private_phase1_t *this,
						 auth_method_t method, bool local)
{
	bool initiator;

	initiator = local == this->initiator;
	if (initiator && method == AUTH_HYBRID_INIT_RSA)
	{
		return TRUE;
	}
	if (!initiator && method == AUTH_HYBRID_RESP_RSA)
	{
		return TRUE;
	}
	return FALSE;
}
