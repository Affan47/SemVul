sysblk_get_host_blks(struct ppa_addr ppa, int nr_blks, u8 *blks,
								void *private)
{
	struct sysblk_scan *s = private;
	int i, nr_sysblk = 0;

	for (i = 0; i < nr_blks; i++) {
		if (blks[i] != NVM_BLK_T_HOST)
			continue;

		if (s->nr_ppas == MAX_BLKS_PR_SYSBLK * MAX_SYSBLKS) {
			pr_err("nvm: too many host blks\n");
			return -EINVAL;
		}

		ppa.g.blk = i;

		s->ppas[scan_ppa_idx(s->row, nr_sysblk)] = ppa;
		s->nr_ppas++;
		nr_sysblk++;
	}

	return 0;
}
