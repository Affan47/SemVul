yenta_probe_handler(int irq, void *dev_id)
{
	struct yenta_socket *socket = (struct yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;


	cb_event = cb_readl(socket, CB_SOCKET_EVENT);
	cb_writel(socket, CB_SOCKET_EVENT, -1);
	csc = exca_readb(socket, I365_CSC);

	if (cb_event || csc) {
		socket->probe_status = 1;
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}
