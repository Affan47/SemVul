_read_mmap(struct sst *sst, size_t count)
{
	int i;
	int fd;
	int result;
	int fcount;
	int blk_sizes;
	char file[SST_FLEN];
	struct sst_block *blks;
	struct skiplist *merge = NULL;
	struct footer footer;
	int fsize = sizeof(struct footer);

	memset(file, 0, SST_FLEN);
	snprintf(file, SST_FLEN, "%s/%s", sst->basedir, sst->name);

	fd = open(file, O_RDWR, 0644);
	result = lseek(fd, -fsize, SEEK_END);
	if (result == -1) {
		abort();
	}
	result = read(fd, &footer, fsize);
	if (result == -1)
		abort();

	fcount = from_be32(footer.count);

	blk_sizes = fcount * sizeof(struct sst_block);


	blks= mmap(0, blk_sizes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (blks == MAP_FAILED) {
		__DEBUG(LEVEL_ERROR, "%s", "Error:sst_bloom un-mmapping the file");
		goto out;
	}


	merge = skiplist_new(fcount + count + 1);
	for (i = 0; i < fcount; i++) {
			skiplist_insert(merge, blks[i].key, from_be64(blks[i].offset), ADD);
	}

	if (munmap(blks, blk_sizes) == -1)
		__DEBUG(LEVEL_ERROR, "%s", "read_map:un-mmapping the file");

out:
	close(fd);

	return merge;
}
