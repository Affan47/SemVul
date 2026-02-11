ssd_check_temperature(struct ssd_device *dev, int temp)
{
	uint64_t val;
	uint32_t off;
	int cur;
	int i;

	if (mode != SSD_DRV_MODE_STANDARD) {
		return;
	}

	if (dev->protocol_info.ver <= SSD_PROTOCOL_V3) {
	}

	for (i=0; i<dev->hw_info.nr_ctrl; i++) {
		off = SSD_CTRL_TEMP_REG0 + i * sizeof(uint64_t);

		val = ssd_reg_read(dev->ctrlp + off);
		if (val == 0xffffffffffffffffull) {
			continue;
		}

		cur = (int)CUR_TEMP(val);
		if (cur >= temp) {
			if (!test_and_set_bit(SSD_HWMON_TEMP(SSD_TEMP_CTRL), &dev->hwmon)) {
				if (dev->protocol_info.ver > SSD_PROTOCOL_V3 && dev->protocol_info.ver < SSD_PROTOCOL_V3_2_2) {
					hio_warn("%s: Over temperature, please check the fans.\n", dev->name);
					dev->ot_delay = SSD_OT_DELAY;
				}
			}
			return;
		}
	}

	if (test_and_clear_bit(SSD_HWMON_TEMP(SSD_TEMP_CTRL), &dev->hwmon)) {
		if (dev->protocol_info.ver > SSD_PROTOCOL_V3 && dev->protocol_info.ver < SSD_PROTOCOL_V3_2_2) {
			hio_warn("%s: Temperature is OK.\n", dev->name);
			dev->ot_delay = 0;
		}
	}
}
