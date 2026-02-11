query_data(char *buf, size_t buf_len,
			  char *query, size_t query_len)
{
	char *out;
	const char *key;
	struct label_it i;
	struct aa_label *label, *curr;
	struct aa_profile *profile;
	struct aa_data *data;
	u32 bytes;
	u32 blocks;
	u32 size;

	if (!query_len)
		return -EINVAL;

	key = query + strnlen(query, query_len) + 1;
	if (key + 1 >= query + query_len)
		return -EINVAL;
	if (key + strnlen(key, query + query_len - key) >= query + query_len)
		return -EINVAL;

	if (buf_len < sizeof(bytes) + sizeof(blocks))
		return -EINVAL;

	curr = aa_begin_current_label(DO_UPDATE);
	label = aa_label_parse(curr, query, GFP_KERNEL, false, false);
	aa_end_current_label(curr);
	if (IS_ERR(label))
		return PTR_ERR(label);


	memset(buf, 0, sizeof(bytes) + sizeof(blocks));
	out = buf + sizeof(bytes) + sizeof(blocks);

	blocks = 0;
	label_for_each_confined(i, label, profile) {
		if (!profile->data)
			continue;

		data = rhashtable_lookup_fast(profile->data, &key,
					      profile->data->p);

		if (data) {
			if (out + sizeof(size) + data->size > buf + buf_len) {
				aa_put_label(label);
				return -EINVAL;
			}
			size = __cpu_to_le32(data->size);
			memcpy(out, &size, sizeof(size));
			out += sizeof(size);
			memcpy(out, data->data, data->size);
			out += data->size;
			blocks++;
		}
	}
	aa_put_label(label);

	bytes = out - buf - sizeof(bytes);
	bytes = __cpu_to_le32(bytes);
	blocks = __cpu_to_le32(blocks);
	memcpy(buf, &bytes, sizeof(bytes));
	memcpy(buf + sizeof(bytes), &blocks, sizeof(blocks));

	return out - buf;
}
