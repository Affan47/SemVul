line6_send_raw_message_async(struct usb_line6 *line6, const char *buffer,
				 int size)
{
	struct message *msg;
	struct urb *urb;


	msg = kmalloc(sizeof(struct message), GFP_ATOMIC);
	if (msg == NULL)
		return -ENOMEM;


	urb = usb_alloc_urb(0, GFP_ATOMIC);

	if (urb == NULL) {
		kfree(msg);
		return -ENOMEM;
	}


	msg->line6 = line6;
	msg->buffer = buffer;
	msg->size = size;
	msg->done = 0;


	return line6_send_raw_message_async_part(msg, urb);
}
