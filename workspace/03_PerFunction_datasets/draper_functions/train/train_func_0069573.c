gen_unique_name(struct send_ctx *sctx,
			   u64 ino, u64 gen,
			   struct fs_path *dest)
{
	int ret = 0;
	struct btrfs_path *path;
	struct btrfs_dir_item *di;
	char tmp[64];
	int len;
	u64 idx = 0;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	while (1) {
		len = snprintf(tmp, sizeof(tmp), "o%llu-%llu-%llu",
				ino, gen, idx);
		ASSERT(len < sizeof(tmp));

		di = btrfs_lookup_dir_item(NULL, sctx->send_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				tmp, strlen(tmp), 0);
		btrfs_release_path(path);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		}
		if (di) {

			idx++;
			continue;
		}

		if (!sctx->parent_root) {

			ret = 0;
			break;
		}

		di = btrfs_lookup_dir_item(NULL, sctx->parent_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				tmp, strlen(tmp), 0);
		btrfs_release_path(path);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		}
		if (di) {

			idx++;
			continue;
		}

		break;
	}

	ret = fs_path_add(dest, tmp, strlen(tmp));

out:
	btrfs_free_path(path);
	return ret;
}
