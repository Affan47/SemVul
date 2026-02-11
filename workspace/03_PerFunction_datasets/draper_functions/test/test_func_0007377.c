img_hash_finish_req(struct ahash_request *req, int err)
{
	struct img_hash_request_ctx *ctx = ahash_request_ctx(req);
	struct img_hash_dev *hdev =  ctx->hdev;

	if (!err) {
		img_hash_copy_hash(req);
		if (DRIVER_FLAGS_FINAL & hdev->flags)
			err = img_hash_finish(req);
	} else {
		dev_warn(hdev->dev, "Hash failed with error %d\n", err);
		ctx->flags |= DRIVER_FLAGS_ERROR;
	}

	hdev->flags &= ~(DRIVER_FLAGS_DMA_READY | DRIVER_FLAGS_OUTPUT_READY |
		DRIVER_FLAGS_CPU | DRIVER_FLAGS_BUSY | DRIVER_FLAGS_FINAL);

	if (req->base.complete)
		req->base.complete(&req->base, err);
}
