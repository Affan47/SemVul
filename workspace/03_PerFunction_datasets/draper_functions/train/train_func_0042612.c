ipwireless_handle_v1_interrupt(int irq,
						  struct ipw_hardware *hw)
{
	unsigned short irqn;

	irqn = inw(hw->base_port + IOIR);


	if (irqn == 0xFFFF)
		return IRQ_NONE;
	else if (irqn != 0) {
		unsigned short ack = 0;
		unsigned long flags;


		if (irqn & IR_TXINTR) {
			ack |= IR_TXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->tx_ready = 1;
			spin_unlock_irqrestore(&hw->lock, flags);
		}

		if (irqn & IR_RXINTR) {
			ack |= IR_RXINTR;
			spin_lock_irqsave(&hw->lock, flags);
			hw->rx_ready++;
			spin_unlock_irqrestore(&hw->lock, flags);
		}
		if (ack != 0) {
			outw(ack, hw->base_port + IOIR);
			tasklet_schedule(&hw->tasklet);
		}
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}
