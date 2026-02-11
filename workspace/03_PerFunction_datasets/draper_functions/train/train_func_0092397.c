mxuport_prepare_write_buffer(struct usb_serial_port *port,
					void *dest, size_t size)
{
	u8 *buf = dest;
	int count;

	count = kfifo_out_locked(&port->write_fifo, buf + HEADER_SIZE,
				 size - HEADER_SIZE,
				 &port->lock);

	put_unaligned_be16(port->port_number, buf);
	put_unaligned_be16(count, buf + 2);

	dev_dbg(&port->dev, "%s - size %zd count %d\n", __func__,
		size, count);

	return count + HEADER_SIZE;
}
