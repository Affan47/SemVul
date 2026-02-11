inv_check_and_setup_chip(struct inv_mpu6050_state *st,
		const struct i2c_device_id *id)
{
	int result;

	st->chip_type = INV_MPU6050;
	st->hw  = &hw_info[st->chip_type];
	st->reg = hw_info[st->chip_type].reg;


	result = inv_mpu6050_write_reg(st, st->reg->pwr_mgmt_1,
					INV_MPU6050_BIT_H_RESET);
	if (result)
		return result;
	msleep(INV_MPU6050_POWER_UP_TIME);


	result = inv_mpu6050_set_power_itg(st, false);
	if (result)
		return result;
	result = inv_mpu6050_set_power_itg(st, true);
	if (result)
		return result;

	result = inv_mpu6050_switch_engine(st, false,
					INV_MPU6050_BIT_PWR_ACCL_STBY);
	if (result)
		return result;
	result = inv_mpu6050_switch_engine(st, false,
					INV_MPU6050_BIT_PWR_GYRO_STBY);
	if (result)
		return result;

	return 0;
}
