dbFreeBits(struct bmap * bmp, struct dmap * dp, s64 blkno,
		       int nblocks)
{
	int dbitno, word, rembits, nb, nwords, wbitno, nw, agno;
	dmtree_t *tp = (dmtree_t *) & dp->tree;
	int rc = 0;
	int size;


	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;


	assert(dbitno + nblocks <= BPERDMAP);


	for (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) {


		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);


		if (nb < DBWORD) {


			dp->wmap[word] &=
			    cpu_to_le32(~(ONES << (DBWORD - nb)
					  >> wbitno));


			rc = dbJoin(tp, word,
				    dbMaxBud((u8 *) & dp->wmap[word]));
			if (rc)
				return rc;

			word += 1;
		} else {


			nwords = rembits >> L2DBWORD;
			memset(&dp->wmap[word], 0, nwords * 4);


			nb = nwords << L2DBWORD;


			for (; nwords > 0; nwords -= nw) {


				size =
				    min(LITOL2BSZ
					(word, L2LPERDMAP, BUDMIN),
					NLSTOL2BSZ(nwords));


				rc = dbJoin(tp, word, size);
				if (rc)
					return rc;


				nw = BUDSIZE(size, BUDMIN);
				word += nw;
			}
		}
	}


	le32_add_cpu(&dp->nfree, nblocks);

	BMAP_LOCK(bmp);


	agno = blkno >> bmp->db_agl2size;
	bmp->db_nfree += nblocks;
	bmp->db_agfree[agno] += nblocks;


	if ((bmp->db_agfree[agno] == bmp->db_agsize && agno == bmp->db_maxag) ||
	    (agno == bmp->db_numag - 1 &&
	     bmp->db_agfree[agno] == (bmp-> db_mapsize & (BPERDMAP - 1)))) {
		while (bmp->db_maxag > 0) {
			bmp->db_maxag -= 1;
			if (bmp->db_agfree[bmp->db_maxag] !=
			    bmp->db_agsize)
				break;
		}


		if (bmp->db_agpref > bmp->db_maxag)
			bmp->db_agpref = bmp->db_maxag;
	}

	BMAP_UNLOCK(bmp);

	return 0;
}
