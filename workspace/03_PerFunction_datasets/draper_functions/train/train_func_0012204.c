gf_bs_read_data(GF_BitStream *bs, char *data, u32 nbBytes)
{
	u64 orig = bs->position;

	if (bs->position+nbBytes > bs->size) return 0;

	if (BS_IsAlign(bs)) {
		switch (bs->bsmode) {
		case GF_BITSTREAM_READ:
			memcpy(data, bs->original + bs->position, nbBytes);
			bs->position += nbBytes;
			return nbBytes;
		case GF_BITSTREAM_FILE_READ:
		case GF_BITSTREAM_FILE_WRITE:
			if (bs->buffer_io)
				bs_flush_cache(bs);
			nbBytes = fread(data, 1, nbBytes, bs->stream);
			bs->position += nbBytes;
			return nbBytes;
		default:
			return 0;
		}
	}

	while (nbBytes-- > 0) {
		*data++ = gf_bs_read_int(bs, 8);
	}
	return (u32) (bs->position - orig);

}
