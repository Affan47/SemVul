get_lsr_info(struct edgeport_port *edge_port,
						unsigned int __user *value)
{
	unsigned int result = 0;
	unsigned long flags;

	spin_lock_irqsave(&edge_port->ep_lock, flags);
	if (edge_port->maxTxCredits == edge_port->txCredits &&
	    edge_port->txfifo.count == 0) {
		dev_dbg(&edge_port->port->dev, "%s -- Empty\n", __func__);
		result = TIOCSER_TEMT;
	}
	spin_unlock_irqrestore(&edge_port->ep_lock, flags);

	if (copy_to_user(value, &result, sizeof(int)))
		return -EFAULT;
	return 0;
}
