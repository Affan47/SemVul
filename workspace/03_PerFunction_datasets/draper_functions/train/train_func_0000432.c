hackrf_urb_complete_in(struct urb *urb)
{
	struct hackrf_dev *dev = urb->context;
	struct usb_interface *intf = dev->intf;
	struct hackrf_buffer *buffer;
	unsigned int len;

	dev_dbg_ratelimited(&intf->dev, "status=%d length=%u/%u\n", urb->status,
			    urb->actual_length, urb->transfer_buffer_length);

	switch (urb->status) {
	case 0:
	case -ETIMEDOUT:
		break;
	case -ECONNRESET:
	case -ENOENT:
	case -ESHUTDOWN:
		return;
	default:
		dev_err_ratelimited(&intf->dev, "URB failed %d\n", urb->status);
		goto exit_usb_submit_urb;
	}


	buffer = hackrf_get_next_buffer(dev, &dev->rx_buffer_list);
	if (unlikely(buffer == NULL)) {
		dev->vb_full++;
		dev_notice_ratelimited(&intf->dev,
				       "buffer is full - %u packets dropped\n",
				       dev->vb_full);
		goto exit_usb_submit_urb;
	}

	len = min_t(unsigned long, vb2_plane_size(&buffer->vb.vb2_buf, 0),
		    urb->actual_length);
	hackrf_copy_stream(dev, vb2_plane_vaddr(&buffer->vb.vb2_buf, 0),
		    urb->transfer_buffer, len);
	vb2_set_plane_payload(&buffer->vb.vb2_buf, 0, len);
	buffer->vb.sequence = dev->sequence++;
	v4l2_get_timestamp(&buffer->vb.timestamp);
	vb2_buffer_done(&buffer->vb.vb2_buf, VB2_BUF_STATE_DONE);
exit_usb_submit_urb:
	usb_submit_urb(urb, GFP_ATOMIC);
}
