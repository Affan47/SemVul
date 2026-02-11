mnt_table_next_child_fs(struct libmnt_table *tb, struct libmnt_iter *itr,
			struct libmnt_fs *parent, struct libmnt_fs **chld)
{
	struct libmnt_fs *fs;
	int parent_id, lastchld_id = 0, chld_id = 0;

	if (!tb || !itr || !parent)
		return -EINVAL;

	DBG(TAB, mnt_debug_h(tb, "lookup next child of %s",
				mnt_fs_get_target(parent)));

	parent_id = mnt_fs_get_id(parent);
	if (!parent_id)
		return -EINVAL;


	if (itr->head && itr->p != itr->head) {
		MNT_ITER_ITERATE(itr, fs, struct libmnt_fs, ents);
		lastchld_id = mnt_fs_get_id(fs);
	}

	*chld = NULL;

	mnt_reset_iter(itr, MNT_ITER_FORWARD);
	while(mnt_table_next_fs(tb, itr, &fs) == 0) {
		int id;

		if (mnt_fs_get_parent_id(fs) != parent_id)
			continue;

		id = mnt_fs_get_id(fs);

		if ((!lastchld_id || id > lastchld_id) &&
		    (!*chld || id < chld_id)) {
			*chld = fs;
			chld_id = id;
		}
	}

	if (!chld_id)
		return 1;


	mnt_table_set_iter(tb, itr, *chld);

	return 0;
}
