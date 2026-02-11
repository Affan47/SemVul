tlv_length_check(char *name, icq_tlv_t *t, int length) {
	if (t->len == length)
		return 0;

	debug_error("%s Incorrect TVL type=0x%02x. Length=%d, should be %d.\n", name, t->type, t->len, length);
	return 1;
}
