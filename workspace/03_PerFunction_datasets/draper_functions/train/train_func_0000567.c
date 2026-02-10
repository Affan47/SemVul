is_sdma_eng_name(char *buf, size_t bsize, unsigned int source)
{

	unsigned int what  = source / TXE_NUM_SDMA_ENGINES;

	unsigned int which = source % TXE_NUM_SDMA_ENGINES;

	if (likely(what < 3))
		snprintf(buf, bsize, "%s%u", sdma_int_names[what], which);
	else
		snprintf(buf, bsize, "Invalid SDMA interrupt %u", source);
	return buf;
}
