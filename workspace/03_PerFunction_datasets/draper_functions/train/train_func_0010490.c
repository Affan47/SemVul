ssd_clear_warning(struct ssd_device *dev)
{
	uint32_t off, size;
	int i, ret = 0;

	if (dev->protocol_info.ver <= SSD_PROTOCOL_V3) {
		return 0;
	}


	memset(&dev->smart.log_info, 0, sizeof(dev->smart.log_info));


	dev->smart.io_stat.nr_to = 0;
	dev->smart.io_stat.nr_rwerr = 0;
	dev->smart.io_stat.nr_ioerr = 0;


	memset(&dev->smart.ecc_info, 0, sizeof(dev->smart.ecc_info));


	for (i=0; i<dev->nr_queue; i++) {

		dev->queue[i].io_stat.nr_to = 0;
		dev->queue[i].io_stat.nr_rwerr = 0;
		dev->queue[i].io_stat.nr_ioerr = 0;


		memset(&(dev->queue[i].ecc_info), 0, sizeof(dev->queue[i].ecc_info));
	}


	for (i = 0; i < dev->rom_info.nr_smart; i++) {
		off = dev->rom_info.smart_base + (dev->rom_info.smart_sz * i);
		size = dev->rom_info.smart_sz;

		ret = ssd_spi_erase(dev, off, size);
		if (ret) {
			hio_warn("%s: warning erase: failed with code 1\n", dev->name);
			goto out;
		}

		size = sizeof(struct ssd_smart);

		ret = ssd_spi_write(dev, &dev->smart, off, size);
		if (ret) {
			hio_warn("%s: warning erase: failed with code 2\n", dev->name);
			goto out;
		}
	}

	dev->smart.version++;


	atomic_set(&dev->tocnt, 0);


	memset(&dev->log_info, 0, sizeof(dev->log_info));

out:
	return ret;
}
