wait_msr_change(struct fwtty_port *port, unsigned long mask)
{
	struct async_icount prev;

	prev = port->icount;

	return wait_event_interruptible(port->port.delta_msr_wait,
					check_msr_delta(port, mask, &prev));
}
