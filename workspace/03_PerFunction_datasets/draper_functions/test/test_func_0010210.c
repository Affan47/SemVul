get_delta_base(
	struct git_pack_file *p,
	git_mwindow **w_curs,
	git_off_t *curpos,
	git_otype type,
	git_off_t delta_obj_offset)
{
	unsigned int left = 0;
	unsigned char *base_info;
	git_off_t base_offset;
	git_oid unused;

	base_info = pack_window_open(p, w_curs, *curpos, &left);

	if (base_info == NULL)
		return GIT_EBUFS;


	if (type == GIT_OBJ_OFS_DELTA) {
		unsigned used = 0;
		unsigned char c = base_info[used++];
		base_offset = c & 127;
		while (c & 128) {
			if (left <= used)
				return GIT_EBUFS;
			base_offset += 1;
			if (!base_offset || MSB(base_offset, 7))
				return 0;
			c = base_info[used++];
			base_offset = (base_offset << 7) + (c & 127);
		}
		base_offset = delta_obj_offset - base_offset;
		if (base_offset <= 0 || base_offset >= delta_obj_offset)
			return 0;
		*curpos += used;
	} else if (type == GIT_OBJ_REF_DELTA) {

		if (p->has_cache) {
			int pos;
			struct git_pack_entry key;

			git_oid_fromraw(&key.sha1, base_info);
			pos = git_vector_bsearch(&p->cache, &key);
			if (pos >= 0) {
				*curpos += 20;
				return ((struct git_pack_entry *)git_vector_get(&p->cache, pos))->offset;
			}
		}

		if (pack_entry_find_offset(&base_offset, &unused, p, (git_oid *)base_info, GIT_OID_HEXSZ) < 0)
			return packfile_error("base entry delta is not in the same pack");
		*curpos += 20;
	} else
		return 0;

	return base_offset;
}
