txRelease(struct tblock * tblk)
{
	struct metapage *mp;
	lid_t lid;
	struct tlock *tlck;

	TXN_LOCK();

	for (lid = tblk->next; lid; lid = tlck->next) {
		tlck = lid_to_tlock(lid);
		if ((mp = tlck->mp) != NULL &&
		    (tlck->type & tlckBTROOT) == 0) {
			assert(mp->xflag & COMMIT_PAGE);
			mp->lid = 0;
		}
	}


	TXN_WAKEUP(&tblk->waitor);

	TXN_UNLOCK();
}
