slave_device_init(const char *path, void *block_list)
{
	struct slave_device *device = NULL;
	struct block_device *block;

	block = _get_block(path, block_list);
	if (block) {
		device = malloc(sizeof(struct slave_device));
		if (device) {
			device->raid = NULL;
			device->state = _get_state(path);
			device->slot = _get_slot(path);
			device->errors = _get_errors(path);
			device->block = block;
		}
	}
	return device;
}
