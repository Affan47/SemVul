send_extent_data(struct send_ctx *sctx,
			    const u64 offset,
			    const u64 len)
{
	u64 sent = 0;

	if (sctx->flags & BTRFS_SEND_FLAG_NO_FILE_DATA)
		return send_update_extent(sctx, offset, len);

	while (sent < len) {
		u64 size = len - sent;
		int ret;

		if (size > BTRFS_SEND_READ_SIZE)
			size = BTRFS_SEND_READ_SIZE;
		ret = send_write(sctx, offset + sent, size);
		if (ret < 0)
			return ret;
		if (!ret)
			break;
		sent += ret;
	}
	return 0;
}
