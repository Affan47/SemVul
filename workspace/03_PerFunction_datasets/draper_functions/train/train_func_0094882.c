initsm_run_state(struct fpi_ssm *ssm)
{
	struct fp_dev *dev = ssm->dev;
	struct upeke2_dev *upekdev = dev->priv;
	struct libusb_transfer *transfer;
	int r;

	switch (ssm->cur_state) {
	case WRITE_CTRL400: ;
		unsigned char *data;

		transfer = libusb_alloc_transfer(0);
		if (!transfer) {
			fpi_ssm_mark_aborted(ssm, -ENOMEM);
			break;
		}

		data = g_malloc(LIBUSB_CONTROL_SETUP_SIZE + 1);
		libusb_fill_control_setup(data,
			LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE, 0x0c, 0x100, 0x0400, 1);
		libusb_fill_control_transfer(transfer, ssm->dev->udev, data,
			ctrl400_cb, ssm, TIMEOUT);

		r = libusb_submit_transfer(transfer);
		if (r < 0) {
			g_free(data);
			libusb_free_transfer(transfer);
			fpi_ssm_mark_aborted(ssm, r);
		}
		break;
	case READ_MSG03:
		initsm_read_msg_handler(ssm, read_msg03_cb);
		break;
	case SEND_RESP03: ;
		transfer = alloc_send_cmdresponse_transfer(dev, ++upekdev->seq,
			init_resp03, sizeof(init_resp03), initsm_send_msg_cb, ssm);
		if (!transfer) {
			fpi_ssm_mark_aborted(ssm, -ENOMEM);
			break;
		}

		r = libusb_submit_transfer(transfer);
		if (r < 0) {
			g_free(transfer->buffer);
			libusb_free_transfer(transfer);
			fpi_ssm_mark_aborted(ssm, r);
		}
		break;
	case READ_MSG05:
		initsm_read_msg_handler(ssm, read_msg05_cb);
		break;
	case SEND28_06: ;
		unsigned char dummy28_06 = 0x04;
		upekdev->seq = 0xf0;
		initsm_send_msg28_handler(ssm, 0x06, &dummy28_06, 1);
		break;
	case READ28_06:
		initsm_read_msg_handler(ssm, read28_06_cb);
		break;
    case SEND28_51: ;
		unsigned char dummy28_51[] = { 0x04, 0x0a, 0x00, 0x00, 0x00 };
		initsm_send_msg28_handler(ssm, 0x51, dummy28_51, 5);
		break;
	case READ28_51:
		initsm_read_msg_handler(ssm, read28_51_cb);
		break;
	case SEND28_07: ;
		unsigned char dummy28_07[] = { 0x04, 0x20, 0x00, 0x00, 0x00 };
		initsm_send_msg28_handler(ssm, 0x07, dummy28_07, 5);
		break;
	case READ28_07:
		initsm_read_msg_handler(ssm, read28_07_cb);
		break;
	case SEND28_08:
		initsm_send_msg28_handler(ssm, 0x08, init28_08, sizeof(init28_08));
		break;
	case READ28_08:
		initsm_read_msg_handler(ssm, read28_08_cb);
		break;
	}
}
