BitStream_allocate(BitStream *bstream, int length)
{
	unsigned char *data;

	if(bstream == NULL) {
		return -1;
	}

	data = (unsigned char *)malloc(length);
	if(data == NULL) {
		return -1;
	}

	if(bstream->data) {
		free(bstream->data);
	}
	bstream->length = length;
	bstream->data = data;

	return 0;
}
