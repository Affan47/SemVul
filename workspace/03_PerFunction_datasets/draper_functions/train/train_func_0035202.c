__find_xattr(int num, struct btrfs_key *di_key,
			const char *name, int name_len,
			const char *data, int data_len,
			u8 type, void *vctx)
{
	struct find_xattr_ctx *ctx = vctx;

	if (name_len == ctx->name_len &&
	    strncmp(name, ctx->name, name_len) == 0) {
		ctx->found_idx = num;
		ctx->found_data_len = data_len;
		ctx->found_data = kmemdup(data, data_len, GFP_NOFS);
		if (!ctx->found_data)
			return -ENOMEM;
		return 1;
	}
	return 0;
}
