c67x00_handle_successful_td(struct c67x00_hcd *c67x00,
					struct c67x00_td *td)
{
	struct urb *urb = td->urb;

	if (!urb)
		return;

	urb->actual_length += td_actual_bytes(td);

	switch (usb_pipetype(td->pipe)) {

	case PIPE_CONTROL:
		switch (td->privdata) {
		case SETUP_STAGE:
			urb->interval =
			    urb->transfer_buffer_length ?
			    DATA_STAGE : STATUS_STAGE;

			urb->actual_length = 0;
			break;

		case DATA_STAGE:
			if (c67x00_end_of_data(td)) {
				urb->interval = STATUS_STAGE;
				c67x00_clear_pipe(c67x00, td);
			}
			break;

		case STATUS_STAGE:
			urb->interval = 0;
			c67x00_giveback_urb(c67x00, urb, 0);
			break;
		}
		break;

	case PIPE_INTERRUPT:
	case PIPE_BULK:
		if (unlikely(c67x00_end_of_data(td))) {
			c67x00_clear_pipe(c67x00, td);
			c67x00_giveback_urb(c67x00, urb, 0);
		}
		break;
	}
}
