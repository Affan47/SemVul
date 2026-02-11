token_is_valid(const sectoken_t *tok, const knode_t *kn)
{


	STATIC_ASSERT(T_REFRESH_PERIOD * T_KEYS >= 3600);

	return sectoken_is_valid(token_stg, tok, kn->addr,
		(kn->flags & KNODE_F_FIREWALLED) ? T_FW_PORT : kn->port);
}
