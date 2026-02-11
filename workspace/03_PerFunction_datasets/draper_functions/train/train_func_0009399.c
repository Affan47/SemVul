my_device_create(struct controlvm_message *inmsg)
{
	struct controlvm_message_packet *cmd = &inmsg->cmd;
	u32 bus_no = cmd->create_device.bus_no;
	u32 dev_no = cmd->create_device.dev_no;
	struct visor_device *dev_info = NULL;
	struct visor_device *bus_info;
	struct visorchannel *visorchannel;
	int rc = CONTROLVM_RESP_SUCCESS;

	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, NULL);
	if (!bus_info) {
		POSTCODE_LINUX_4(DEVICE_CREATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_BUS_INVALID;
		goto cleanup;
	}

	if (bus_info->state.created == 0) {
		POSTCODE_LINUX_4(DEVICE_CREATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_BUS_INVALID;
		goto cleanup;
	}

	dev_info = visorbus_get_device_by_id(bus_no, dev_no, NULL);
	if (dev_info && (dev_info->state.created == 1)) {
		POSTCODE_LINUX_4(DEVICE_CREATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_ALREADY_DONE;
		goto cleanup;
	}

	dev_info = kzalloc(sizeof(*dev_info), GFP_KERNEL);
	if (!dev_info) {
		POSTCODE_LINUX_4(DEVICE_CREATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_KMALLOC_FAILED;
		goto cleanup;
	}

	dev_info->chipset_bus_no = bus_no;
	dev_info->chipset_dev_no = dev_no;
	dev_info->inst = cmd->create_device.dev_inst_uuid;


	dev_info->device.parent = &bus_info->device;

	POSTCODE_LINUX_4(DEVICE_CREATE_ENTRY_PC, dev_no, bus_no,
			 POSTCODE_SEVERITY_INFO);

	visorchannel =
	       visorchannel_create_with_lock(cmd->create_device.channel_addr,
					     cmd->create_device.channel_bytes,
					     GFP_KERNEL,
					     cmd->create_device.data_type_uuid);

	if (!visorchannel) {
		POSTCODE_LINUX_4(DEVICE_CREATE_FAILURE_PC, dev_no, bus_no,
				 POSTCODE_SEVERITY_ERR);
		rc = -CONTROLVM_RESP_ERROR_KMALLOC_FAILED;
		kfree(dev_info);
		dev_info = NULL;
		goto cleanup;
	}
	dev_info->visorchannel = visorchannel;
	dev_info->channel_type_guid = cmd->create_device.data_type_uuid;
	POSTCODE_LINUX_4(DEVICE_CREATE_EXIT_PC, dev_no, bus_no,
			 POSTCODE_SEVERITY_INFO);
cleanup:
	device_epilog(dev_info, segment_state_running,
		      CONTROLVM_DEVICE_CREATE, &inmsg->hdr, rc,
		      inmsg->hdr.flags.response_expected == 1, 1);
}
