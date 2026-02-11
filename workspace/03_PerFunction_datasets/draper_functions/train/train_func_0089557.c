BuildLAYR() {
	struct Chunk * LAYRChunk;
	unsigned char * LAYRData;

	if ((LAYRChunk = (struct Chunk *) malloc(sizeof(struct Chunk))) == NULL) {
		fprintf(stderr, "Insufficient memory to allocate LAYR chunk\n");
		return NULL;
	}

	if ((LAYRData = (unsigned char *) malloc(20)) == NULL) {
		fprintf(stderr, "Insufficient memory to allocate LAYR data\n");
		free(LAYRChunk);
		return NULL;
	}

	ShortAsBytes(0, LAYRData);
	memset(LAYRData + 2, (char) NULL, 16);
	strcpy(LAYRData + 2, "Default layer");
	*(LAYRData + 18) = LF_ACTIVE | LF_DISPLAYED;
	*(LAYRData + 19) = 0;

	strncpy(LAYRChunk->ID, "LAYR", 4);
	LAYRChunk->Size = 20;
	LAYRChunk->Data = LAYRData;

	return LAYRChunk;
}
