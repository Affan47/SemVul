sm5502_init_dev_type(struct sm5502_muic_info *info)
{
	unsigned int reg_data, vendor_id, version_id;
	int i, ret;


	ret = regmap_read(info->regmap, SM5502_REG_DEVICE_ID, &reg_data);
	if (ret) {
		dev_err(info->dev,
			"failed to read DEVICE_ID register: %d\n", ret);
		return;
	}

	vendor_id = ((reg_data & SM5502_REG_DEVICE_ID_VENDOR_MASK) >>
				SM5502_REG_DEVICE_ID_VENDOR_SHIFT);
	version_id = ((reg_data & SM5502_REG_DEVICE_ID_VERSION_MASK) >>
				SM5502_REG_DEVICE_ID_VERSION_SHIFT);

	dev_info(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
			    version_id, vendor_id);


	for (i = 0; i < info->num_reg_data; i++) {
		unsigned int val = 0;

		if (!info->reg_data[i].invert)
			val |= ~info->reg_data[i].val;
		else
			val = info->reg_data[i].val;
		regmap_write(info->regmap, info->reg_data[i].reg, val);
	}
}
