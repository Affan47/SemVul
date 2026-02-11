get_server_sh(struct proxy *px, const char *addr, int len)
{
	unsigned int h, l;

	if (px->lbprm.tot_weight == 0)
		return NULL;

	l = h = 0;


	if (px->lbprm.tot_used == 1)
		goto hash_done;

	while ((l + sizeof (int)) <= len) {
		h ^= ntohl(*(unsigned int *)(&addr[l]));
		l += sizeof (int);
	}
	if ((px->lbprm.algo & BE_LB_HASH_MOD) == BE_LB_HMOD_AVAL)
		h = full_hash(h);
 hash_done:
	if (px->lbprm.algo & BE_LB_LKUP_CHTREE)
		return chash_get_server_hash(px, h);
	else
		return map_get_server_hash(px, h);
}
