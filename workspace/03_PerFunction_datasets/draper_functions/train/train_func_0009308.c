ecryptfs_init_messaging(struct ecryptfs_messaging_ctx *mctx, uint32_t type)
{
	int rc = 0;

	memset(mctx, 0, sizeof(*mctx));
	switch (type) {
	case ECRYPTFS_MESSAGING_TYPE_MISCDEV:
		mctx->type = ECRYPTFS_MESSAGING_TYPE_MISCDEV;
		rc = ecryptfs_init_miscdev(&mctx->ctx.miscdev_ctx);
		break;
	case ECRYPTFS_MESSAGING_TYPE_NETLINK:

	default:
		rc = -EINVAL;
		goto out;
	};
out:
	return rc;
}
