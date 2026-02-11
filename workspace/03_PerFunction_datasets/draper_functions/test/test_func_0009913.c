send_chmod(struct send_ctx *sctx, u64 ino, u64 gen, u64 mode)
{
	int ret = 0;
	struct fs_path *p;

verbose_printk("btrfs: send_chmod %llu mode=%llu\n", ino, mode);

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_CHMOD);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, ino, gen, p);
	if (ret < 0)
		goto out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_MODE, mode & 07777);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_free(p);
	return ret;
}
