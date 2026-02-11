ezusb_ihex_firmware_download(struct usb_device *dev,
					struct ezusb_fx_type fx,
					const char *firmware_path)
{
	int ret = -ENOENT;
	const struct firmware *firmware = NULL;
	const struct ihex_binrec *record;

	if (request_ihex_firmware(&firmware, firmware_path,
				  &dev->dev)) {
		dev_err(&dev->dev,
			"%s - request \"%s\" failed\n",
			__func__, firmware_path);
		goto out;
	}

	ret = ezusb_set_reset(dev, fx.cpucs_reg, 0);
	if (ret < 0)
		goto out;

	record = (const struct ihex_binrec *)firmware->data;
	for (; record; record = ihex_next_binrec(record)) {
		if (be32_to_cpu(record->addr) > fx.max_internal_adress) {
			ret = ezusb_writememory(dev, be32_to_cpu(record->addr),
						(unsigned char *)record->data,
						be16_to_cpu(record->len), WRITE_EXT_RAM);
			if (ret < 0) {
				dev_err(&dev->dev, "%s - ezusb_writememory "
					"failed writing internal memory "
					"(%d %04X %p %d)\n", __func__, ret,
					be32_to_cpu(record->addr), record->data,
					be16_to_cpu(record->len));
				goto out;
			}
		}
	}

	ret = ezusb_set_reset(dev, fx.cpucs_reg, 1);
	if (ret < 0)
		goto out;
	record = (const struct ihex_binrec *)firmware->data;
	for (; record; record = ihex_next_binrec(record)) {
		if (be32_to_cpu(record->addr) <= fx.max_internal_adress) {
			ret = ezusb_writememory(dev, be32_to_cpu(record->addr),
						(unsigned char *)record->data,
						be16_to_cpu(record->len), WRITE_INT_RAM);
			if (ret < 0) {
				dev_err(&dev->dev, "%s - ezusb_writememory "
					"failed writing external memory "
					"(%d %04X %p %d)\n", __func__, ret,
					be32_to_cpu(record->addr), record->data,
					be16_to_cpu(record->len));
				goto out;
			}
		}
	}
	ret = ezusb_set_reset(dev, fx.cpucs_reg, 0);
out:
	release_firmware(firmware);
	return ret;
}
