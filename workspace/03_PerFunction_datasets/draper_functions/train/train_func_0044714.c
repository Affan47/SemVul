v_handle_resp00(struct fp_dev *dev, unsigned char *data,
	size_t data_len)
{
	unsigned char status;
	int r = 0;

	if (data_len != 14) {
		fp_err("received 3001 poll response of %d bytes?", data_len);
		r = -EPROTO;
		goto out;
	}

	status = data[5];
	fp_dbg("poll result = %02x", status);


	switch (status) {
	case 0x0c:
		break;
	case 0x20:
		fp_dbg("processing scan for verification");
		break;
	case 0x00:
		fp_dbg("good image");
		break;
	case 0x1c:
	case 0x0b:
	case 0x23:
		r = FP_VERIFY_RETRY;
		break;
	case 0x0f:
		r = FP_VERIFY_RETRY_REMOVE_FINGER;
		break;
	case 0x1e:
		r = FP_VERIFY_RETRY_TOO_SHORT;
		break;
	case 0x24:
		r = FP_VERIFY_RETRY_CENTER_FINGER;
		break;
	default:
		fp_err("unrecognised verify status code %02x", status);
		r = -EPROTO;
	}

out:
	if (r)
		fpi_drvcb_report_verify_result(dev, r, NULL);
	if (r >= 0)
		verify_iterate(dev);
}
