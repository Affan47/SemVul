aac_rx_select_comm(struct aac_dev *dev, int comm)
{
	switch (comm) {
	case AAC_COMM_PRODUCER:
		dev->a_ops.adapter_enable_int = aac_rx_enable_interrupt_producer;
		dev->a_ops.adapter_intr = aac_rx_intr_producer;
		dev->a_ops.adapter_deliver = aac_rx_deliver_producer;
		break;
	case AAC_COMM_MESSAGE:
		dev->a_ops.adapter_enable_int = aac_rx_enable_interrupt_message;
		dev->a_ops.adapter_intr = aac_rx_intr_message;
		dev->a_ops.adapter_deliver = aac_rx_deliver_message;
		break;
	default:
		return 1;
	}
	return 0;
}
