map_get_server_hash(struct proxy *px, unsigned int hash)
{
	if (px->lbprm.tot_weight == 0)
		return NULL;

	if (px->lbprm.map.state & LB_MAP_RECALC)
		recalc_server_map(px);

	return px->lbprm.map.srv[hash % px->lbprm.tot_weight];
}
