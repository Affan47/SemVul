visorchannel_write(struct visorchannel *channel, ulong offset,
		   void *local, ulong nbytes)
{
	size_t chdr_size = sizeof(struct channel_header);
	size_t copy_size;

	if (offset + nbytes > channel->nbytes)
		return -EIO;

	if (offset < chdr_size) {
		copy_size = min(chdr_size - offset, nbytes);
		memcpy(((char *)(&channel->chan_hdr)) + offset,
		       local, copy_size);
	}

	memcpy(channel->mapped + offset, local, nbytes);

	return 0;
}
