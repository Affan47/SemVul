xmmsv_coll_set_idlist (xmmsv_coll_t *coll, int ids[])
{
	unsigned int i;

	xmmsv_list_clear (coll->idlist);
	for (i = 0; ids[i]; i++) {
		xmmsv_list_append_int (coll->idlist, ids[i]);
	}
}
