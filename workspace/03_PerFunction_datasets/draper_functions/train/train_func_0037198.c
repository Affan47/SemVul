verify_packfile(struct packed_git *p,
		struct pack_window **w_curs)
{
	off_t index_size = p->index_size;
	const unsigned char *index_base = p->index_data;
	SHA_CTX ctx;
	unsigned char sha1[20];
	off_t offset = 0, pack_sig = p->pack_size - 20;
	uint32_t nr_objects, i;
	int err;
	struct idx_entry *entries;


	SHA1_Init(&ctx);
	while (offset < pack_sig) {
		unsigned int remaining;
		unsigned char *in = use_pack(p, w_curs, offset, &remaining);
		offset += remaining;
		if (offset > pack_sig)
			remaining -= (unsigned int)(offset - pack_sig);
		SHA1_Update(&ctx, in, remaining);
	}
	SHA1_Final(sha1, &ctx);
	if (hashcmp(sha1, use_pack(p, w_curs, pack_sig, NULL)))
		return error("Packfile %s SHA1 mismatch with itself",
			     p->pack_name);
	if (hashcmp(sha1, index_base + index_size - 40))
		return error("Packfile %s SHA1 mismatch with idx",
			     p->pack_name);
	unuse_pack(w_curs);


	nr_objects = p->num_objects;
	entries = xmalloc(nr_objects * sizeof(*entries));

	for (i = 0; i < nr_objects; i++) {
		entries[i].sha1 = nth_packed_object_sha1(p, i);
		if (!entries[i].sha1)
			die("internal error pack-check nth-packed-object");
		entries[i].offset = find_pack_entry_one(entries[i].sha1, p);
		if (!entries[i].offset)
			die("internal error pack-check find-pack-entry-one");
	}
	qsort(entries, nr_objects, sizeof(*entries), compare_entries);

	for (i = 0, err = 0; i < nr_objects; i++) {
		void *data;
		enum object_type type;
		unsigned long size;

		data = unpack_entry(p, entries[i].offset, &type, &size);
		if (!data) {
			err = error("cannot unpack %s from %s",
				    sha1_to_hex(entries[i].sha1), p->pack_name);
			continue;
		}
		if (check_sha1_signature(entries[i].sha1, data, size, typename(type))) {
			err = error("packed %s from %s is corrupt",
				    sha1_to_hex(entries[i].sha1), p->pack_name);
			free(data);
			continue;
		}
		free(data);
	}
	free(entries);

	return err;
}
