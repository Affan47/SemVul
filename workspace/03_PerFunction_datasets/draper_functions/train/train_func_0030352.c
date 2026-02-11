gf_bs_del(GF_BitStream *bs)
{
	if (!bs) return;

	if ((bs->bsmode == GF_BITSTREAM_WRITE_DYN) && bs->original) gf_free(bs->original);
	if (bs->buffer_io)
		bs_flush_cache(bs);
	gf_free(bs);
}
