dbAllocBottomUp(struct inode *ip, s64 blkno, s64 nblocks)
{
	struct metapage *mp;
	struct dmap *dp;
	int nb, rc;
	s64 lblkno, rem;
	struct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	struct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);


	ASSERT(nblocks <= bmp->db_mapsize - blkno);


	mp = NULL;
	for (rem = nblocks; rem > 0; rem -= nb, blkno += nb) {

		if (mp) {
			write_metapage(mp);
		}


		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = read_metapage(ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL) {
			IREAD_UNLOCK(ipbmap);
			return -EIO;
		}
		dp = (struct dmap *) mp->data;


		nb = min(rem, BPERDMAP - (blkno & (BPERDMAP - 1)));


		if ((rc = dbAllocDmapBU(bmp, dp, blkno, nb))) {
			release_metapage(mp);
			IREAD_UNLOCK(ipbmap);
			return (rc);
		}
	}


	write_metapage(mp);

	IREAD_UNLOCK(ipbmap);

	return (0);
}
