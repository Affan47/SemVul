ssd_clear_smart(struct ssd_device *dev)
{
	struct timeval tv;
	uint64_t sversion;
	uint32_t off, length;
	int i;
	int ret;

	if (dev->protocol_info.ver <= SSD_PROTOCOL_V3) {
		return 0;
	}


	off = dev->rom_info.smart_base;
	length = dev->rom_info.smart_sz * dev->rom_info.nr_smart;

	ret = ssd_spi_erase(dev, off, length);
	if (ret) {
		hio_warn("%s: info erase: failed\n", dev->name);
		goto out;
	}

	sversion = dev->smart.version;

	memset(&dev->smart, 0, sizeof(struct ssd_smart));
	dev->smart.version = sversion + 1;
	dev->smart.magic = SSD_SMART_MAGIC;


	for (i=0; i<dev->nr_queue; i++) {
		memset(&(dev->queue[i].io_stat), 0, sizeof(struct ssd_io_stat));
		memset(&(dev->queue[i].ecc_info), 0, sizeof(struct ssd_ecc_info));
	}

	atomic_set(&dev->tocnt, 0);


	memset(&dev->log_info, 0, sizeof(struct ssd_log_info));

	do_gettimeofday(&tv);
	dev->uptime = tv.tv_sec;


out:
	return ret;
}
