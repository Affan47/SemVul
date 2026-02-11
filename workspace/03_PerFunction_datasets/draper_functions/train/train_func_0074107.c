drbd_bm_aio_ctx_destroy(struct kref *kref)
{
	struct drbd_bm_aio_ctx *ctx = container_of(kref, struct drbd_bm_aio_ctx, kref);
	unsigned long flags;

	spin_lock_irqsave(&ctx->device->resource->req_lock, flags);
	list_del(&ctx->list);
	spin_unlock_irqrestore(&ctx->device->resource->req_lock, flags);
	put_ldev(ctx->device);
	kfree(ctx);
}
