mapLog(struct jfs_log * log, struct tblock * tblk, struct lrd * lrd,
		   struct tlock * tlck)
{
	struct pxd_lock *pxdlock;
	int i, nlock;
	pxd_t *pxd;


	if (tlck->type & tlckRELOCATE) {


		lrd->type = cpu_to_le16(LOG_NOREDOPAGE);
		pxdlock = (struct pxd_lock *) & tlck->lock;
		pxd = &lrd->log.redopage.pxd;
		*pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, NULL));


		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		lrd->log.updatemap.type = cpu_to_le16(LOG_FREEPXD);
		lrd->log.updatemap.nxd = cpu_to_le16(1);
		lrd->log.updatemap.pxd = pxdlock->pxd;
		lrd->backchain = cpu_to_le32(lmLog(log, tblk, lrd, NULL));


		tlck->flag |= tlckUPDATEMAP;
		return;
	}


	else {


		lrd->type = cpu_to_le16(LOG_UPDATEMAP);
		pxdlock = (struct pxd_lock *) & tlck->lock;
		nlock = pxdlock->index;
		for (i = 0; i < nlock; i++, pxdlock++) {
			if (pxdlock->flag & mlckALLOCPXD)
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_ALLOCPXD);
			else
				lrd->log.updatemap.type =
				    cpu_to_le16(LOG_FREEPXD);
			lrd->log.updatemap.nxd = cpu_to_le16(1);
			lrd->log.updatemap.pxd = pxdlock->pxd;
			lrd->backchain =
			    cpu_to_le32(lmLog(log, tblk, lrd, NULL));
			jfs_info("mapLog: xaddr:0x%lx xlen:0x%x",
				 (ulong) addressPXD(&pxdlock->pxd),
				 lengthPXD(&pxdlock->pxd));
		}


		tlck->flag |= tlckUPDATEMAP;
	}
}
