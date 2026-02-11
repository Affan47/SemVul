tw_initconnection(TW_Device_Extension *tw_dev, int message_credits)
{
	unsigned long command_que_value;
	TW_Command  *command_packet;
	TW_Response_Queue response_queue;
	int request_id = 0;

	dprintk(KERN_NOTICE "3w-xxxx: tw_initconnection()\n");


	if (tw_dev->command_packet_virtual_address[request_id] == NULL) {
		printk(KERN_WARNING "3w-xxxx: tw_initconnection(): Bad command packet virtual address.\n");
		return 1;
	}

	command_packet = (TW_Command *)tw_dev->command_packet_virtual_address[request_id];
	memset(command_packet, 0, sizeof(TW_Sector));
	command_packet->opcode__sgloffset = TW_OPSGL_IN(0, TW_OP_INIT_CONNECTION);
	command_packet->size = TW_INIT_COMMAND_PACKET_SIZE;
	command_packet->request_id = request_id;
	command_packet->status = 0x0;
	command_packet->flags = 0x0;
	command_packet->byte6.message_credits = message_credits;
	command_packet->byte8.init_connection.response_queue_pointer = 0x0;
	command_que_value = tw_dev->command_packet_physical_address[request_id];

	if (command_que_value == 0) {
		printk(KERN_WARNING "3w-xxxx: tw_initconnection(): Bad command packet physical address.\n");
		return 1;
	}


	outl(command_que_value, TW_COMMAND_QUEUE_REG_ADDR(tw_dev));


	if (tw_poll_status_gone(tw_dev, TW_STATUS_RESPONSE_QUEUE_EMPTY, 30) == 0) {
		response_queue.value = inl(TW_RESPONSE_QUEUE_REG_ADDR(tw_dev));
		request_id = TW_RESID_OUT(response_queue.response_id);

		if (request_id != 0) {

			printk(KERN_WARNING "3w-xxxx: tw_initconnection(): Unexpected request id.\n");
			return 1;
		}
		if (command_packet->status != 0) {

			tw_decode_sense(tw_dev, request_id, 0);
			return 1;
		}
	}
	return 0;
}
