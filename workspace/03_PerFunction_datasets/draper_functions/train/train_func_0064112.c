aoedev_downdev(struct aoedev *d)
{
	struct aoetgt *t, **tt, **te;
	struct list_head *head, *pos, *nx;
	struct request *rq;
	int i;

	d->flags &= ~DEVFL_UP;


	for (i = 0; i < NFACTIVE; i++) {
		head = &d->factive[i];
		list_for_each_safe(pos, nx, head)
			downdev_frame(pos);
	}
	head = &d->rexmitq;
	list_for_each_safe(pos, nx, head)
		downdev_frame(pos);


	tt = d->targets;
	te = tt + d->ntargets;
	for (; tt < te && (t = *tt); tt++) {
		aoecmd_wreset(t);
		t->nout = 0;
	}


	aoe_failip(d);


	if (d->blkq) {
		while ((rq = blk_peek_request(d->blkq))) {
			blk_start_request(rq);
			aoe_end_request(d, rq, 1);
		}
	}

	if (d->gd)
		set_capacity(d->gd, 0);
}
