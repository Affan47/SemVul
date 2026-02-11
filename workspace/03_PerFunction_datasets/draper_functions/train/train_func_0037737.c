buffer_append_long(buffer *b, long val) {
	if (!b) return -1;

	buffer_prepare_append(b, 32);
	if (b->used == 0)
		b->used++;

	b->used += LI_ltostr(b->ptr + (b->used - 1), val);
	return 0;
}
