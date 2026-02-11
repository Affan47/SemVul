__wa_seg_submit(struct wa_rpipe *rpipe, struct wa_xfer *xfer,
			   struct wa_seg *seg, int *dto_done)
{
	int result;


	*dto_done = 1;


	wa_xfer_get(xfer);

	seg->status = WA_SEG_SUBMITTED;
	result = usb_submit_urb(&seg->tr_urb, GFP_ATOMIC);
	if (result < 0) {
		pr_err("%s: xfer %p#%u: REQ submit failed: %d\n",
		       __func__, xfer, seg->index, result);
		wa_xfer_put(xfer);
		goto error_tr_submit;
	}

	if (seg->isoc_pack_desc_urb) {
		wa_xfer_get(xfer);
		result = usb_submit_urb(seg->isoc_pack_desc_urb, GFP_ATOMIC);
		seg->isoc_frame_index = 0;
		if (result < 0) {
			pr_err("%s: xfer %p#%u: ISO packet descriptor submit failed: %d\n",
			       __func__, xfer, seg->index, result);
			wa_xfer_put(xfer);
			goto error_iso_pack_desc_submit;
		}
	}

	if (seg->dto_urb) {
		struct wahc *wa = xfer->wa;
		wa_xfer_get(xfer);
		result = usb_submit_urb(seg->dto_urb, GFP_ATOMIC);
		if (result < 0) {
			pr_err("%s: xfer %p#%u: DTO submit failed: %d\n",
			       __func__, xfer, seg->index, result);
			wa_xfer_put(xfer);
			goto error_dto_submit;
		}


		if (((wa->quirks & WUSB_QUIRK_ALEREON_HWA_CONCAT_ISOC) == 0)
			&& (seg->isoc_frame_count > 1))
			*dto_done = 0;
	}
	rpipe_avail_dec(rpipe);
	return 0;

error_dto_submit:
	usb_unlink_urb(seg->isoc_pack_desc_urb);
error_iso_pack_desc_submit:
	usb_unlink_urb(&seg->tr_urb);
error_tr_submit:
	seg->status = WA_SEG_ERROR;
	seg->result = result;
	*dto_done = 1;
	return result;
}
