ezusb_req_enqueue_run(struct ezusb_priv *upriv,
				  struct request_context *ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&upriv->req_lock, flags);

	if (!ctx->upriv->udev) {
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		goto done;
	}
	atomic_inc(&ctx->refcount);
	list_add_tail(&ctx->list, &upriv->req_pending);
	spin_unlock_irqrestore(&upriv->req_lock, flags);

	ctx->state = EZUSB_CTX_QUEUED;
	ezusb_req_queue_run(upriv);

 done:
	return;
}
