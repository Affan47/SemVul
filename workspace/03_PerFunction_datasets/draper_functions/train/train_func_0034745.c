tw_post_command_packet(TW_Device_Extension *tw_dev, int request_id)
{
	u32 status_reg_value;
	unsigned long command_que_value;

	dprintk(KERN_NOTICE "3w-xxxx: tw_post_command_packet()\n");
	command_que_value = tw_dev->command_packet_physical_address[request_id];
	status_reg_value = inl(TW_STATUS_REG_ADDR(tw_dev));

	if (tw_check_bits(status_reg_value)) {
		dprintk(KERN_WARNING "3w-xxxx: tw_post_command_packet(): Unexpected bits.\n");
		tw_decode_bits(tw_dev, status_reg_value, 1);
	}

	if ((status_reg_value & TW_STATUS_COMMAND_QUEUE_FULL) == 0) {

		outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));
		tw_dev->state[request_id] = TW_S_POSTED;
		tw_dev->posted_request_count++;
		if (tw_dev->posted_request_count > tw_dev->max_posted_request_count) {
			tw_dev->max_posted_request_count = tw_dev->posted_request_count;
		}
	} else {

		if (tw_dev->state[request_id] != TW_S_PENDING) {
			tw_dev->state[request_id] = TW_S_PENDING;
			tw_dev->pending_request_count++;
			if (tw_dev->pending_request_count > tw_dev->max_pending_request_count) {
				tw_dev->max_pending_request_count = tw_dev->pending_request_count;
			}
			tw_dev->pending_queue[tw_dev->pending_tail] = request_id;
			if (tw_dev->pending_tail == TW_Q_LENGTH-1) {
				tw_dev->pending_tail = TW_Q_START;
			} else {
				tw_dev->pending_tail = tw_dev->pending_tail + 1;
			}
		}
		TW_UNMASK_COMMAND_INTERRUPT(tw_dev);
		return 1;
	}
	return 0;
}
