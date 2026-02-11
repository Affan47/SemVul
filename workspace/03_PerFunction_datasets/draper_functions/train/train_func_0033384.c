rdu_merge(struct rdu *p)
{
	int err;
	unsigned long long ul;
	union au_rdu_ent_ul u;
	void *t;

	err = -1;
#if 0
	u = p->ent;
	for (ul = 0; ul < p->npos; ul++) {
		DPri("%p, %.*s\n", u.e, u.e->nlen, u.e->name);
		u.ul += au_rdu_len(u.e->nlen);
	}
#endif

	p->pos = realloc(p->pos, sizeof(*p->pos) * p->npos);
	if (!p->pos)
		goto out;

	err = 0;
	p->idx = 0;
	p->real = NULL;
	p->wh = NULL;
	u = p->ent;
	for (ul = 0; !err && ul < p->npos; ul++) {

		u.e->wh = 0;
		do_store = 1;
		if (u.e->nlen <= AUFS_WH_PFX_LEN
		    || memcmp(u.e->name, AUFS_WH_PFX, AUFS_WH_PFX_LEN))
			err = rdu_ent_append(p, u.e);
		else
			err = rdu_ent_append_wh(p, u.e);
		u.ul += au_rdu_len(u.e->nlen);
	}
	tdestroy(p->real, rdu_tfree);
	tdestroy(p->wh, rdu_tfree);
	if (err) {
		free(p->pos);
		p->pos = NULL;
		goto out;
	} else if (p->idx == p->npos)
		goto out;

	p->npos = p->idx;

	t = realloc(p->pos, sizeof(*p->pos) * p->idx);
	if (t)
		p->pos = t;

	u = p->ent;
	for (ul = 0; ul < p->npos; ul++) {
		if (p->pos[ul] != u.e)
			break;
		u.ul += au_rdu_len(u.e->nlen);
	}
	for (; ul < p->npos; ul++) {
		memmove(u.e, p->pos[ul], au_rdu_len(p->pos[ul]->nlen));
		p->pos[ul] = u.e;
		u.ul += au_rdu_len(u.e->nlen);
	}

 out:
	return err;
}
