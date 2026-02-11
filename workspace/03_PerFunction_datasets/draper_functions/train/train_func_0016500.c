sysblk_get_free_blks(struct ppa_addr ppa, int nr_blks, u8 *blks,
								void *private)
{
	struct sysblk_scan *s = private;
	struct ppa_addr *sppa;
	int i, blkid = 0;

	for (i = 0; i < nr_blks; i++) {
		if (blks[i] == NVM_BLK_T_HOST)
			return -EEXIST;

		if (blks[i] != NVM_BLK_T_FREE)
			continue;

		sppa = &s->ppas[scan_ppa_idx(s->row, blkid)];
		sppa->g.ch = ppa.g.ch;
		sppa->g.lun = ppa.g.lun;
		sppa->g.blk = i;
		s->nr_ppas++;
		blkid++;

		pr_debug("nvm: use (%u %u %u) as sysblk\n",
					sppa->g.ch, sppa->g.lun, sppa->g.blk);
		if (blkid > MAX_BLKS_PR_SYSBLK - 1)
			return 0;
	}

	pr_err("nvm: sysblk failed get sysblk\n");
	return -EINVAL;
}
