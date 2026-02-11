ecryptfs_messaging_exit(struct ecryptfs_messaging_ctx *mctx)
{
	int rc = 0;

	switch (mctx->type) {
	case ECRYPTFS_MESSAGING_TYPE_MISCDEV:
		ecryptfs_release_miscdev(&mctx->ctx.miscdev_ctx);
		break;
	default:
		rc = -EINVAL;
		goto out;
	};
out:
	return rc;
}
