addtgt(struct aoedev *d, char *addr, ulong nframes)
{
	struct aoetgt *t, **tt, **te;

	tt = d->targets;
	te = tt + d->ntargets;
	for (; tt < te && *tt; tt++)
		;

	if (tt == te) {
		tt = grow_targets(d);
		if (!tt)
			goto nomem;
	}
	t = kzalloc(sizeof(*t), GFP_ATOMIC);
	if (!t)
		goto nomem;
	t->nframes = nframes;
	t->d = d;
	memcpy(t->addr, addr, sizeof t->addr);
	t->ifp = t->ifs;
	aoecmd_wreset(t);
	t->maxout = t->nframes / 2;
	INIT_LIST_HEAD(&t->ffree);
	return *tt = t;

 nomem:
	pr_info("aoe: cannot allocate memory to add target\n");
	return NULL;
}
