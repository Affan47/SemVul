find_unique_script_block(state_t *s, byte *buf, int type)
{
	int magic_pos_adder = s->version >= SCI_VERSION_FTU_NEW_SCRIPT_HEADER ? 0 : 2;

	buf += magic_pos_adder;
	do {
		int seeker_type = getUInt16(buf);
		int seeker_size;

		if (seeker_type == 0) break;
		if (seeker_type == type) return buf;

		seeker_size = getUInt16(buf + 2);
		buf += seeker_size;
	} while(1);

	return NULL;
}
