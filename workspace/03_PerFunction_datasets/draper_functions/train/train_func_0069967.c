remove_one(struct dm_btree_info *info, dm_block_t root,
		      uint64_t *keys, uint64_t end_key,
		      dm_block_t *new_root, unsigned *nr_removed)
{
	unsigned level, last_level = info->levels - 1;
	int index = 0, r = 0;
	struct shadow_spine spine;
	struct btree_node *n;
	struct dm_btree_value_type le64_vt;
	uint64_t k;

	init_le64_type(info->tm, &le64_vt);
	init_shadow_spine(&spine, info);
	for (level = 0; level < last_level; level++) {
		r = remove_raw(&spine, info, &le64_vt,
			       root, keys[level], (unsigned *) &index);
		if (r < 0)
			goto out;

		n = dm_block_data(shadow_current(&spine));
		root = value64(n, index);
	}

	r = remove_nearest(&spine, info, &info->value_type,
			   root, keys[last_level], &index);
	if (r < 0)
		goto out;

	n = dm_block_data(shadow_current(&spine));

	if (index < 0)
		index = 0;

	if (index >= le32_to_cpu(n->header.nr_entries)) {
		r = -ENODATA;
		goto out;
	}

	k = le64_to_cpu(n->keys[index]);
	if (k >= keys[last_level] && k < end_key) {
		if (info->value_type.dec)
			info->value_type.dec(info->value_type.context,
					     value_ptr(n, index));

		delete_at(n, index);
		keys[last_level] = k + 1ull;

	} else
		r = -ENODATA;

out:
	*new_root = shadow_root(&spine);
	exit_shadow_spine(&spine);

	return r;
}
