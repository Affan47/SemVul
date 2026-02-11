send_rmdir(struct send_ctx *sctx, struct fs_path *path)
{
	int ret;

verbose_printk("btrfs: send_rmdir %s\n", path->start);

	ret = begin_cmd(sctx, BTRFS_SEND_C_RMDIR);
	if (ret < 0)
		goto out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	return ret;
}
