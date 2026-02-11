create_index(void)
{
	static char tmpfile[PATH_MAX];
	SHA_CTX ctx;
	struct sha1file *f;
	struct object_entry **idx, **c, **last, *e;
	struct object_entry_pool *o;
	uint32_t array[256];
	int i, idx_fd;


	idx = xmalloc(object_count * sizeof(struct object_entry*));
	c = idx;
	for (o = blocks; o; o = o->next_pool)
		for (e = o->next_free; e-- != o->entries;)
			if (pack_id == e->pack_id)
				*c++ = e;
	last = idx + object_count;
	if (c != last)
		die("internal consistency error creating the index");
	qsort(idx, object_count, sizeof(struct object_entry*), oecmp);


	c = idx;
	for (i = 0; i < 256; i++) {
		struct object_entry **next = c;;
		while (next < last) {
			if ((*next)->sha1[0] != i)
				break;
			next++;
		}
		array[i] = htonl(next - idx);
		c = next;
	}

	snprintf(tmpfile, sizeof(tmpfile),
		"%s/pack/tmp_idx_XXXXXX", get_object_directory());
	idx_fd = xmkstemp(tmpfile);
	f = sha1fd(idx_fd, tmpfile);
	sha1write(f, array, 256 * sizeof(int));
	SHA1_Init(&ctx);
	for (c = idx; c != last; c++) {
		uint32_t offset = htonl((*c)->offset);
		sha1write(f, &offset, 4);
		sha1write(f, (*c)->sha1, sizeof((*c)->sha1));
		SHA1_Update(&ctx, (*c)->sha1, 20);
	}
	sha1write(f, pack_data->sha1, sizeof(pack_data->sha1));
	sha1close(f, NULL, CSUM_FSYNC);
	free(idx);
	SHA1_Final(pack_data->sha1, &ctx);
	return tmpfile;
}
