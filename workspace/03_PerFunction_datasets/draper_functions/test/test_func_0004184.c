wa_seg_tr_cb(struct urb *urb)
{
	struct wa_seg *seg = urb->context;
	struct wa_xfer *xfer = seg->xfer;
	struct wahc *wa;
	struct device *dev;
	struct wa_rpipe *rpipe;
	unsigned long flags;
	unsigned rpipe_ready;
	u8 done = 0;

	switch (urb->status) {
	case 0:
		spin_lock_irqsave(&xfer->lock, flags);
		wa = xfer->wa;
		dev = &wa->usb_iface->dev;
		dev_dbg(dev, "xfer %p ID 0x%08X#%u: request done\n",
			xfer, wa_xfer_id(xfer), seg->index);
		if (xfer->is_inbound &&
			seg->status < WA_SEG_PENDING &&
			!(usb_pipeisoc(xfer->urb->pipe)))
			seg->status = WA_SEG_PENDING;
		spin_unlock_irqrestore(&xfer->lock, flags);
		break;
	case -ECONNRESET:
	case -ENOENT:
		break;
	default:
		spin_lock_irqsave(&xfer->lock, flags);
		wa = xfer->wa;
		dev = &wa->usb_iface->dev;
		rpipe = xfer->ep->hcpriv;
		if (printk_ratelimit())
			dev_err(dev, "xfer %p ID 0x%08X#%u: request error %d\n",
				xfer, wa_xfer_id(xfer), seg->index,
				urb->status);
		if (edc_inc(&wa->nep_edc, EDC_MAX_ERRORS,
			    EDC_ERROR_TIMEFRAME)){
			dev_err(dev, "DTO: URB max acceptable errors "
				"exceeded, resetting device\n");
			wa_reset_all(wa);
		}
		usb_unlink_urb(seg->isoc_pack_desc_urb);
		usb_unlink_urb(seg->dto_urb);
		seg->result = urb->status;
		__wa_xfer_abort(xfer);
		rpipe_ready = rpipe_avail_inc(rpipe);
		done = __wa_xfer_mark_seg_as_done(xfer, seg, WA_SEG_ERROR);
		spin_unlock_irqrestore(&xfer->lock, flags);
		if (done)
			wa_xfer_completion(xfer);
		if (rpipe_ready)
			wa_xfer_delayed_run(rpipe);
	}

	wa_xfer_put(xfer);
}
