f2fs_end_io_crypto_work(struct f2fs_crypto_ctx *ctx, struct bio *bio)
{
	INIT_WORK(&ctx->r.work, completion_pages);
	ctx->r.bio = bio;
	queue_work(f2fs_read_workqueue, &ctx->r.work);
}
