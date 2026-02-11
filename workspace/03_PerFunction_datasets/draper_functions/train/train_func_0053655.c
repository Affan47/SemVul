csio_rn_lookup(struct csio_lnode *ln, uint32_t flowid)
{
	struct csio_rnode *rnhead = (struct csio_rnode *) &ln->rnhead;
	struct list_head *tmp;
	struct csio_rnode *rn;

	list_for_each(tmp, &rnhead->sm.sm_list) {
		rn = (struct csio_rnode *) tmp;
		if (rn->flowid == flowid)
			return rn;
	}

	return NULL;
}
