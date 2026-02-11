ezusb_request_in_callback(struct ezusb_priv *upriv,
				      struct urb *urb)
{
	struct ezusb_packet *ans = urb->transfer_buffer;
	struct request_context *ctx = NULL;
	enum ezusb_state state;
	unsigned long flags;


	spin_lock_irqsave(&upriv->req_lock, flags);
	if (upriv->udev) {
		struct list_head *item;

		list_for_each(item, &upriv->req_active) {
			struct request_context *c;
			int reply_count;

			c = list_entry(item, struct request_context, list);
			reply_count =
			    ezusb_reply_inc(c->buf->req_reply_count);
			if ((ans->ans_reply_count == reply_count)
			    && (le16_to_cpu(ans->hermes_rid) == c->in_rid)) {
				ctx = c;
				break;
			}
			netdev_dbg(upriv->dev, "Skipped (0x%x/0x%x) (%d/%d)\n",
				   le16_to_cpu(ans->hermes_rid), c->in_rid,
				   ans->ans_reply_count, reply_count);
		}
	}

	if (ctx == NULL) {
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		err("%s: got unexpected RID: 0x%04X", __func__,
		    le16_to_cpu(ans->hermes_rid));
		ezusb_req_queue_run(upriv);
		return;
	}


	urb->transfer_buffer = ctx->buf;
	ctx->buf = (void *) ans;
	ctx->buf_length = urb->actual_length;

	state = ctx->state;
	switch (state) {
	case EZUSB_CTX_REQ_SUBMITTED:


		ctx->state = EZUSB_CTX_RESP_RECEIVED;
		spin_unlock_irqrestore(&upriv->req_lock, flags);


		break;

	case EZUSB_CTX_REQ_COMPLETE:


		ctx->state = EZUSB_CTX_COMPLETE;


		del_timer(&ctx->timer);
		spin_unlock_irqrestore(&upriv->req_lock, flags);


		ezusb_ctx_complete(ctx);
		break;

	default:
		spin_unlock_irqrestore(&upriv->req_lock, flags);

		pr_warn("Matched IN URB, unexpected context state(0x%x)\n",
			state);

		del_timer(&ctx->timer);
		ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
		usb_unlink_urb(ctx->outurb);
		ezusb_req_queue_run(upriv);
		break;
	}
}
