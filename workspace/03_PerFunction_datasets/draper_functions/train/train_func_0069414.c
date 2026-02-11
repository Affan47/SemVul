igb_init_thermal_sensor_thresh_generic(struct e1000_hw *hw)
{
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  low_thresh_delta;
	u8  num_sensors;
	u8  sensor_index;
	u8  sensor_location;
	u8  therm_limit;
	u8  i;
	struct e1000_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	if ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		return E1000_NOT_IMPLEMENTED;

	memset(data, 0, sizeof(struct e1000_thermal_sensor_data));

	data->sensor[0].location = 0x1;
	data->sensor[0].caution_thresh =
		(rd32(E1000_THHIGHTC) & 0xFF);
	data->sensor[0].max_op_thresh =
		(rd32(E1000_THLOWTC) & 0xFF);


	hw->nvm.ops.read(hw, NVM_ETS_CFG, 1, &ets_offset);
	if ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		return 0;

	hw->nvm.ops.read(hw, ets_offset, 1, &ets_cfg);
	if (((ets_cfg & NVM_ETS_TYPE_MASK) >> NVM_ETS_TYPE_SHIFT)
	    != NVM_ETS_TYPE_EMC)
		return E1000_NOT_IMPLEMENTED;

	low_thresh_delta = ((ets_cfg & NVM_ETS_LTHRES_DELTA_MASK) >>
			    NVM_ETS_LTHRES_DELTA_SHIFT);
	num_sensors = (ets_cfg & NVM_ETS_NUM_SENSORS_MASK);

	for (i = 1; i <= num_sensors; i++) {
		hw->nvm.ops.read(hw, (ets_offset + i), 1, &ets_sensor);
		sensor_index = ((ets_sensor & NVM_ETS_DATA_INDEX_MASK) >>
				NVM_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & NVM_ETS_DATA_LOC_MASK) >>
				   NVM_ETS_DATA_LOC_SHIFT);
		therm_limit = ets_sensor & NVM_ETS_DATA_HTHRESH_MASK;

		hw->phy.ops.write_i2c_byte(hw,
			e1000_emc_therm_limit[sensor_index],
			E1000_I2C_THERMAL_SENSOR_ADDR,
			therm_limit);

		if ((i < E1000_MAX_SENSORS) && (sensor_location != 0)) {
			data->sensor[i].location = sensor_location;
			data->sensor[i].caution_thresh = therm_limit;
			data->sensor[i].max_op_thresh = therm_limit -
							low_thresh_delta;
		}
	}
	return 0;
}
