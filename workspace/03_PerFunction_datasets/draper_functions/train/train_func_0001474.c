dump_child_devices(int length)
{
	struct bdb_block *block;
	struct bdb_child_devices *child_devs;
	struct child_device_config *child;
	int i;

	block = find_section(BDB_CHILD_DEVICE_TABLE, length);
	if (!block) {
		printf("No child device table found\n");
		return;
	}

	child_devs = block->data;

	printf("Child devices block:\n");
	for (i = 0; i < DEVICE_CHILD_SIZE; i++) {
		child = &child_devs->children[i];

		if (!child->device_type)
			continue;
		printf("\tChild device %d\n", i);
		printf("\t\tType: 0x%04x (%s)\n", child->device_type,
		       child_device_type(child->device_type));
		printf("\t\tDVO port: 0x%02x\n", child->dvo_port);
		printf("\t\tI2C pin: 0x%02x\n", child->i2c_pin);
		printf("\t\tSlave addr: 0x%02x\n", child->slave_addr);
		printf("\t\tDDC pin: 0x%02x\n", child->ddc_pin);
		printf("\t\tDVO config: 0x%02x\n", child->dvo_cfg);
		printf("\t\tDVO wiring: 0x%02x\n", child->dvo_wiring);
	}

	free(block);
}
