dtTruncateEntry(dtpage_t * p, int ti, struct dt_lock ** dtlock)
{
	int tsi;
	s8 *stbl;
	struct dtslot *t;
	int si, freecnt;
	struct dt_lock *dtlck = *dtlock;
	struct lv *lv;
	int fsi, xsi, n;


	stbl = DT_GETSTBL(p);
	tsi = stbl[ti];


	if (dtlck->index >= dtlck->maxcnt)
		dtlck = (struct dt_lock *) txLinelock(dtlck);
	lv = & dtlck->lv[dtlck->index];

	lv->offset = tsi;


	t = &p->slot[tsi];
	ASSERT(p->header.flag & BT_INTERNAL);
	((struct idtentry *) t)->namlen = 0;
	si = ((struct idtentry *) t)->next;
	((struct idtentry *) t)->next = -1;

	n = 1;
	freecnt = 0;
	fsi = si;
	xsi = tsi;


	while (si >= 0) {

		if (si != xsi + 1) {

			lv->length = n;
			dtlck->index++;


			if (dtlck->index < dtlck->maxcnt)
				lv++;
			else {
				dtlck = (struct dt_lock *) txLinelock(dtlck);
				lv = & dtlck->lv[0];
			}

			lv->offset = si;
			n = 0;
		}

		n++;
		xsi = si;
		freecnt++;

		t = &p->slot[si];
		t->cnt = 1;
		si = t->next;
	}


	lv->length = n;
	dtlck->index++;

	*dtlock = dtlck;


	if (freecnt == 0)
		return;
	t->next = p->header.freelist;
	p->header.freelist = fsi;
	p->header.freecnt += freecnt;
}
