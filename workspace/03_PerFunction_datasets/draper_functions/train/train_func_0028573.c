mpu6050_calc_offset()
{
	const portTickType xPeriod = (30UL / portTICK_RATE_ONE_THIRD_MS);

	imu_data_t imu_readings;
	int i = 0;
	status_code_t twi_status = 0;

    for (i = 0; i < 100; i++)
    {
        mpu6050_read_motion(&imu_readings);
        vTaskDelay(xPeriod);
    }

	int64_t temp_accl_x = 0;
	int64_t temp_accl_y = 0;
	int64_t temp_accl_z = 0;
	int64_t temp_gyro_x = 0;
	int64_t temp_gyro_y = 0;
	int64_t temp_gyro_z = 0;


	for (i = 0; i < 2000; i++)
	{
		mpu6050_read_motion(&imu_readings);
		temp_accl_x += (int64_t)imu_readings.accl_x;
		temp_accl_y += (int64_t)imu_readings.accl_y;
		temp_accl_z += (int64_t)imu_readings.accl_z;
		temp_gyro_x += (int64_t)imu_readings.gyro_x;
		temp_gyro_y += (int64_t)imu_readings.gyro_y;
		temp_gyro_z += (int64_t)imu_readings.gyro_z;

		vTaskDelay(xPeriod);
	}

	offset.accl_x = (int16_t)(temp_accl_x / 2000);
	offset.accl_y = (int16_t)(temp_accl_y / 2000);
	offset.accl_z = (int16_t)(temp_accl_z / 2000);
	offset.gyro_x = (int16_t)(temp_gyro_x / 2000);
	offset.gyro_y = (int16_t)(temp_gyro_y / 2000);
	offset.gyro_z = (int16_t)(temp_gyro_z / 2000);
}
