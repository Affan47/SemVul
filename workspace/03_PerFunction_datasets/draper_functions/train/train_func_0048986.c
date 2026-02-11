ovl_dir_read_merged(struct dentry *dentry, struct list_head *list)
{
	int err;
	struct path realpath;
	struct ovl_readdir_data rdd = {
		.ctx.actor = ovl_fill_merge,
		.dentry = dentry,
		.list = list,
		.root = RB_ROOT,
		.is_merge = false,
		.is_legacy = ovl_config_legacy(dentry),
	};
	int idx, next;

	for (idx = 0; idx != -1; idx = next) {
		next = ovl_path_next(idx, dentry, &realpath);

		err = ovl_dentry_root_may(dentry, &realpath, MAY_READ);
		if (err)
			break;

		if (next != -1) {
			err = ovl_dir_read(&realpath, &rdd);
			if (err)
				break;
		} else {


			list_add(&rdd.middle, rdd.list);
			rdd.is_merge = true;
			err = ovl_dir_read(&realpath, &rdd);
			list_del(&rdd.middle);
		}
	}
	return err;
}
