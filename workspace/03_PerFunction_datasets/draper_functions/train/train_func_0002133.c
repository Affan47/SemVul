print_err_status(struct cx231xx *dev, int packet, int status)
{
	char *errmsg = "Unknown";

	switch (status) {
	case -ENOENT:
		errmsg = "unlinked synchronuously";
		break;
	case -ECONNRESET:
		errmsg = "unlinked asynchronuously";
		break;
	case -ENOSR:
		errmsg = "Buffer error (overrun)";
		break;
	case -EPIPE:
		errmsg = "Stalled (device not responding)";
		break;
	case -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		break;
	case -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		break;
	case -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		break;
	case -ETIME:
		errmsg = "Device does not respond";
		break;
	}
	if (packet < 0) {
		dev_err(dev->dev,
			"URB status %d [%s].\n", status, errmsg);
	} else {
		dev_err(dev->dev,
			"URB packet %d, status %d [%s].\n",
			packet, status, errmsg);
	}
}
