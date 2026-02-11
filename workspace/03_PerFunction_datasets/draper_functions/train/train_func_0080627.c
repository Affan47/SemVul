safe_prepare_write_buffer(struct usb_serial_port *port,
						void *dest, size_t size)
{
	unsigned char *buf = dest;
	int count;
	int trailer_len;
	int pkt_len;
	__u16 fcs;

	trailer_len = safe ? 2 : 0;

	count = kfifo_out_locked(&port->write_fifo, buf, size - trailer_len,
								&port->lock);
	if (!safe)
		return count;


	if (padded) {
		pkt_len = size;
		memset(buf + count, '0', pkt_len - count - trailer_len);
	} else {
		pkt_len = count + trailer_len;
	}


	buf[pkt_len - 2] = count << 2;
	buf[pkt_len - 1] = 0;


	fcs = fcs_compute10(buf, pkt_len, CRC10_INITFCS);
	buf[pkt_len - 2] |= fcs >> 8;
	buf[pkt_len - 1] |= fcs & 0xff;

	return pkt_len;
}
