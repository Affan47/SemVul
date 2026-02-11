gf_bs_write_byte(GF_BitStream *bs, u8 byte, u32 repeat_count)
{
	if (!BS_IsAlign(bs) || bs->buffer_io) {
		u32 count = 0;
		while (count<repeat_count) {
			gf_bs_write_int(bs, byte, 8);
			count++;
		}
		return count;
	}

	switch (bs->bsmode) {
	case GF_BITSTREAM_WRITE:
		if (bs->position + repeat_count > bs->size)
			return 0;
		memset(bs->original + bs->position, byte, repeat_count);
		bs->position += repeat_count;
		return repeat_count;
	case GF_BITSTREAM_WRITE_DYN:

		if (bs->position+repeat_count> bs->size) {
			if (bs->size + repeat_count > 0xFFFFFFFF)
				return 0;
			bs->original = (char*)gf_realloc(bs->original, sizeof(u32)*((u32) bs->size + repeat_count));
			if (!bs->original)
				return 0;
			bs->size += repeat_count;
		}
		memset(bs->original + bs->position, byte, repeat_count);
		bs->position += repeat_count;
		return repeat_count;
	case GF_BITSTREAM_FILE_READ:
	case GF_BITSTREAM_FILE_WRITE:

		if (gf_fwrite(&byte, 1, repeat_count, bs->stream) != repeat_count) return 0;
		if (bs->size == bs->position) bs->size += repeat_count;
		bs->position += repeat_count;
		return repeat_count;
	default:
		return 0;
	}
}
