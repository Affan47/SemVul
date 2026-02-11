BitStream_newFromBytes(int size, unsigned char *data)
{
	unsigned char mask;
	int i, j;
	unsigned char *p;
	BitStream *bstream;

	bstream = BitStream_new();
	if(bstream == NULL) return NULL;

	if(BitStream_allocate(bstream, size * 8)) {
		BitStream_free(bstream);
		return NULL;
	}

	p = bstream->data;
	for(i=0; i<size; i++) {
		mask = 0x80;
		for(j=0; j<8; j++) {
			if(data[i] & mask) {
				*p = 1;
			} else {
				*p = 0;
			}
			p++;
			mask = mask >> 1;
		}
	}

	return bstream;
}
