journal_header_encode(journal_header_t *cooked, journal_rawheader_t *raw) {
	unsigned char flags = 0;

	INSIST(sizeof(cooked->format) == sizeof(raw->h.format));
	memset(raw->pad, 0, sizeof(raw->pad));
	memmove(raw->h.format, cooked->format, sizeof(raw->h.format));
	journal_pos_encode(&raw->h.begin, &cooked->begin);
	journal_pos_encode(&raw->h.end, &cooked->end);
	encode_uint32(cooked->index_size, raw->h.index_size);
	encode_uint32(cooked->sourceserial, raw->h.sourceserial);
	if (cooked->serialset)
		flags |= JOURNAL_SERIALSET;
	raw->h.flags = flags;
}
