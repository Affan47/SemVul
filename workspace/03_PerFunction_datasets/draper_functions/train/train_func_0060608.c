rdu_ent_append_wh(struct rdu *p, struct au_rdu_ent *ent)
{
	int err;

	err = 0;
	ent->wh = 1;
	if (tsearch(ent, (void *)&p->wh, rdu_ent_compar_wh2)) {
		if (p->shwh && do_store)
			rdu_store(p, ent);
	} else
		err = -1;

	return err;
}
