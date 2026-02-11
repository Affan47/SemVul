alloc_buffers(
	unsigned MaxB3Connection,
	unsigned MaxB3Blks,
	unsigned MaxSizeB3)
{
	struct applinfo *ap;
	unsigned nbufs = 2 + MaxB3Connection * (MaxB3Blks + 1);
	size_t recvbuffersize = 128 + MaxSizeB3;
	unsigned i;
	size_t size;

	if (recvbuffersize < 2048)
		recvbuffersize = 2048;

	size = sizeof(struct applinfo);
	size += sizeof(struct recvbuffer) * nbufs;
	size += recvbuffersize * nbufs;

	ap = (struct applinfo *)malloc(size);
	if (ap == 0)
		return 0;

	memset(ap, 0, size);
	ap->maxbufs = nbufs;
	ap->recvbuffersize = recvbuffersize;
	ap->buffers = (struct recvbuffer *)(ap+1);
	ap->firstfree = ap->buffers;
	ap->bufferstart = (unsigned char *)(ap->buffers+nbufs);
	for (i = 0; i < ap->maxbufs; i++) {
		ap->buffers[i].next = &ap->buffers[i+1];
		ap->buffers[i].used = 0;
		ap->buffers[i].ncci = 0;
		ap->buffers[i].buf = ap->bufferstart+(recvbuffersize*i);
	}
	ap->lastfree = &ap->buffers[ap->maxbufs-1];
	ap->lastfree->next = 0;
	return ap;
}
