twa_post_command_packet(TW_Device_Extension *tw_dev, int request_id, char internal)
{
	u32 status_reg_value;
	dma_addr_t command_que_value;
	int retval = 1;

	command_que_value = tw_dev->command_packet_phys[request_id];


	if ((tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9650SE) ||
	    (tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9690SA)) {
		command_que_value += TW_COMMAND_OFFSET;
		writel((u32)command_que_value, TW_COMMAND_QUEUE_REG_ADDR_LARGE(tw_dev));
	}

	status_reg_value = readl(TW_STATUS_REG_ADDR(tw_dev));

	if (twa_check_bits(status_reg_value))
		twa_decode_bits(tw_dev, status_reg_value);

	if (((tw_dev->pending_request_count > 0) && (tw_dev->state[request_id] != TW_S_PENDING)) || (status_reg_value & TW_STATUS_COMMAND_QUEUE_FULL)) {


		if (!internal) {
			retval = SCSI_MLQUEUE_HOST_BUSY;
			goto out;
		}


		if (tw_dev->state[request_id] != TW_S_PENDING) {
			tw_dev->state[request_id] = TW_S_PENDING;
			tw_dev->pending_request_count++;
			if (tw_dev->pending_request_count > tw_dev->max_pending_request_count) {
				tw_dev->max_pending_request_count = tw_dev->pending_request_count;
			}
			tw_dev->pending_queue[tw_dev->pending_tail] = request_id;
			tw_dev->pending_tail = (tw_dev->pending_tail + 1) % TW_Q_LENGTH;
		}
		TW_UNMASK_COMMAND_INTERRUPT(tw_dev);
		goto out;
	} else {
		if ((tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9650SE) ||
		    (tw_dev->tw_pci_dev->device == PCI_DEVICE_ID_3WARE_9690SA)) {

			writel((u32)((u64)command_que_value >> 32), TW_COMMAND_QUEUE_REG_ADDR_LARGE(tw_dev) + 0x4);
		} else {
			if (sizeof(dma_addr_t) > 4) {
				command_que_value += TW_COMMAND_OFFSET;
				writel((u32)command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
				writel((u32)((u64)command_que_value >> 32), TW_COMMAND_QUEUE_REG_ADDR(tw_dev) + 0x4);
			} else {
				writel(TW_COMMAND_OFFSET + command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
			}
		}
		tw_dev->state[request_id] = TW_S_POSTED;
		tw_dev->posted_request_count++;
		if (tw_dev->posted_request_count > tw_dev->max_posted_request_count) {
			tw_dev->max_posted_request_count = tw_dev->posted_request_count;
		}
	}
	retval = 0;
out:
	return retval;
}
