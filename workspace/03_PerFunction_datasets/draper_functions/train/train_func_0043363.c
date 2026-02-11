hts221_probe(struct iio_dev *iio_dev)
{
	struct hts221_hw *hw = iio_priv(iio_dev);
	int err;
	u8 data;

	mutex_init(&hw->lock);

	err = hts221_check_whoami(hw);
	if (err < 0)
		return err;

	hw->odr = hts221_odr_table[0].hz;

	iio_dev->modes = INDIO_DIRECT_MODE;
	iio_dev->dev.parent = hw->dev;
	iio_dev->available_scan_masks = hts221_scan_masks;
	iio_dev->channels = hts221_channels;
	iio_dev->num_channels = ARRAY_SIZE(hts221_channels);
	iio_dev->name = HTS221_DEV_NAME;
	iio_dev->info = &hts221_info;


	err = hts221_parse_rh_caldata(hw);
	if (err < 0) {
		dev_err(hw->dev, "failed to get rh calibration data\n");
		return err;
	}

	data = hts221_avg_list[HTS221_SENSOR_H].avg_avl[3].avg;
	err = hts221_update_avg(hw, HTS221_SENSOR_H, data);
	if (err < 0) {
		dev_err(hw->dev, "failed to set rh oversampling ratio\n");
		return err;
	}


	err = hts221_parse_temp_caldata(hw);
	if (err < 0) {
		dev_err(hw->dev,
			"failed to get temperature calibration data\n");
		return err;
	}

	data = hts221_avg_list[HTS221_SENSOR_T].avg_avl[3].avg;
	err = hts221_update_avg(hw, HTS221_SENSOR_T, data);
	if (err < 0) {
		dev_err(hw->dev,
			"failed to set temperature oversampling ratio\n");
		return err;
	}

	if (hw->irq > 0) {
		err = hts221_allocate_buffers(hw);
		if (err < 0)
			return err;

		err = hts221_allocate_trigger(hw);
		if (err)
			return err;
	}

	return devm_iio_device_register(hw->dev, iio_dev);
}
