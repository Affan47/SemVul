handle_multichannel_storage(struct hv_device *device, int max_chns)
{
	struct storvsc_device *stor_device;
	int num_cpus = num_online_cpus();
	int num_sc;
	struct storvsc_cmd_request *request;
	struct vstor_packet *vstor_packet;
	int ret, t;

	num_sc = ((max_chns > num_cpus) ? num_cpus : max_chns);
	stor_device = get_out_stor_device(device);
	if (!stor_device)
		return;

	stor_device->num_sc = num_sc;
	request = &stor_device->init_request;
	vstor_packet = &request->vstor_packet;

	stor_device->open_sub_channel = true;


	vmbus_set_sc_create_callback(device->channel, handle_sc_creation);


	if (vmbus_are_subchannels_present(device->channel))
		return;

	stor_device->open_sub_channel = false;


	memset(request, 0, sizeof(struct storvsc_cmd_request));
	init_completion(&request->wait_event);
	vstor_packet->operation = VSTOR_OPERATION_CREATE_SUB_CHANNELS;
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;
	vstor_packet->sub_channel_count = num_sc;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (sizeof(struct vstor_packet) -
			       vmscsi_size_delta),
			       (unsigned long)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	if (ret != 0)
		return;

	t = wait_for_completion_timeout(&request->wait_event, 10*HZ);
	if (t == 0)
		return;

	if (vstor_packet->operation != VSTOR_OPERATION_COMPLETE_IO ||
	    vstor_packet->status != 0)
		return;


	stor_device->open_sub_channel = true;
	vmbus_are_subchannels_present(device->channel);
}
