ahash_def_finup_done2(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;

	if (err == -EINPROGRESS)
		return;

	ahash_restore_req(areq, err);

	areq->base.complete(&areq->base, err);
}
