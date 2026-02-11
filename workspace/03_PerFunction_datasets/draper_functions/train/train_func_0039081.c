printFatWithOffset(Stream_t *Stream, off_t offset) {
	File_t *This = getUnbufferedFile(Stream);
	unsigned long n;
	int rel;
	off_t clusSize;

	n = This->FirstAbsCluNr;
	if(!n) {
		printf("Root directory or empty file\n");
		return;
	}

	clusSize = This->Fs->cluster_size * This->Fs->sector_size;

	rel = 0;
	while(offset >= clusSize) {
		n = fatDecode(This->Fs, n);
		rel++;
		if(loopDetect(This, rel, n) < 0)
			return;
		if(n > This->Fs->last_fat)
			return;
		offset -= clusSize;
	}

	printf("%lu", n);
}
