STORAGE_GetCapacity (uint8_t lun, uint32_t *block_num, uint32_t *block_size) {
	if (disk_ioctl(0, GET_SECTOR_COUNT, block_num) != 0) {
		return (-1);
	}
	if (disk_ioctl(0, GET_SECTOR_SIZE, block_size) != 0) {
		return (-1);
	}

	return (0);
}
