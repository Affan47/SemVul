ib_mad_remove_device(struct ib_device *device, void *client_data)
{
	int i;

	for (i = rdma_start_port(device); i <= rdma_end_port(device); i++) {
		if (!rdma_cap_ib_mad(device, i))
			continue;

		if (ib_agent_port_close(device, i))
			dev_err(&device->dev,
				"Couldn't close port %d for agents\n", i);
		if (ib_mad_port_close(device, i))
			dev_err(&device->dev, "Couldn't close port %d\n", i);
	}
}
