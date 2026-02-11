megaraid_isr(int irq, void *devp)
{
	adapter_t	*adapter = devp;
	int		handled;

	handled = megaraid_ack_sequence(adapter);


	if (!adapter->quiescent) {
		megaraid_mbox_runpendq(adapter, NULL);
	}

	return IRQ_RETVAL(handled);
}
