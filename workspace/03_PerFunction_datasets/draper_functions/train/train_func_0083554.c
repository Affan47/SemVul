send_data(enum port_type index, struct nozomi *dc)
{
	u32 size = 0;
	struct port *port = &dc->port[index];
	const u8 toggle = port->toggle_ul;
	void __iomem *addr = port->ul_addr[toggle];
	const u32 ul_size = port->ul_size[toggle];


	size = kfifo_out(&port->fifo_ul, dc->send_buf,
			   ul_size < SEND_BUF_MAX ? ul_size : SEND_BUF_MAX);

	if (size == 0) {
		DBG4("No more data to send, disable link:");
		return 0;
	}


	write_mem32(addr, (u32 *) &size, 4);
	write_mem32(addr + 4, (u32 *) dc->send_buf, size);

	tty_port_tty_wakeup(&port->port);

	return 1;
}
