print_block_details(struct iinfo *ind, int level, int cur_height,
				int pndx, uint64_t file_offset)
{
	struct iinfo *more_indir;
	int more_ind;
	char *tmpbuf;
	uint64_t thisblk;

	thisblk = ind->ii[pndx].block;
	more_indir = malloc(sizeof(struct iinfo));
	if (!more_indir) {
		fprintf(stderr, "Out of memory in function "
			"display_indirect\n");
		return;
	}
	tmpbuf = malloc(sbd.bsize);
	if (!tmpbuf) {
		fprintf(stderr, "Out of memory in function "
			"display_indirect\n");
		free(more_indir);
		return;
	}
	while (thisblk) {
		lseek(sbd.device_fd, thisblk * sbd.bsize, SEEK_SET);

		if (read(sbd.device_fd, tmpbuf, sbd.bsize) != sbd.bsize) {
			fprintf(stderr, "bad read: %s from %s:%d: block %lld "
				"(0x%llx)\n", strerror(errno), __FUNCTION__,
				__LINE__,
				(unsigned long long)ind->ii[pndx].block,
				(unsigned long long)ind->ii[pndx].block);
			exit(-1);
		}
		thisblk = 0;
		memset(more_indir, 0, sizeof(struct iinfo));
		if (S_ISDIR(di.di_mode) && level == di.di_height) {
			thisblk = do_leaf_extended(tmpbuf, more_indir);
			display_leaf(more_indir);
		} else {
			int x;

			for (x = 0; x < 512; x++) {
				memcpy(&more_indir->ii[x].mp,
				       &ind->ii[pndx].mp,
				       sizeof(struct metapath));
				more_indir->ii[x].mp.mp_list[cur_height+1] = x;
			}
			more_ind = _do_indirect_extended(tmpbuf, more_indir,
							 cur_height + 1);
			display_indirect(more_indir, more_ind, level + 1,
					 file_offset);
		}
		if (thisblk) {
			eol(0);
			if (termlines)
				move(line,9);
			print_gfs2("Continuation block 0x%llx / %lld",
				   thisblk, thisblk);
		}
	}
	free(tmpbuf);
	free(more_indir);
}
