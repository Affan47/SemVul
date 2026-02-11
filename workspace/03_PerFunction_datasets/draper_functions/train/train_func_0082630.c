inv_mpu6050_read_fifo(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);
	size_t bytes_per_datum;
	int result;
	u8 data[INV_MPU6050_OUTPUT_DATA_SIZE];
	u16 fifo_count;
	s64 timestamp;

	mutex_lock(&indio_dev->mlock);
	if (!(st->chip_config.accl_fifo_enable |
		st->chip_config.gyro_fifo_enable))
		goto end_session;
	bytes_per_datum = 0;
	if (st->chip_config.accl_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;

	if (st->chip_config.gyro_fifo_enable)
		bytes_per_datum += INV_MPU6050_BYTES_PER_3AXIS_SENSOR;


	result = i2c_smbus_read_i2c_block_data(st->client,
				       st->reg->fifo_count_h,
				       INV_MPU6050_FIFO_COUNT_BYTE, data);
	if (result != INV_MPU6050_FIFO_COUNT_BYTE)
		goto end_session;
	fifo_count = be16_to_cpup((__be16 *)(&data[0]));
	if (fifo_count < bytes_per_datum)
		goto end_session;

	if (fifo_count & 1)
		goto flush_fifo;
	if (fifo_count >  INV_MPU6050_FIFO_THRESHOLD)
		goto flush_fifo;

	if (kfifo_len(&st->timestamps) >
		fifo_count / bytes_per_datum + INV_MPU6050_TIME_STAMP_TOR)
			goto flush_fifo;
	while (fifo_count >= bytes_per_datum) {
		result = i2c_smbus_read_i2c_block_data(st->client,
						       st->reg->fifo_r_w,
						       bytes_per_datum, data);
		if (result != bytes_per_datum)
			goto flush_fifo;

		result = kfifo_out(&st->timestamps, &timestamp, 1);

		if (0 == result)
			timestamp = 0;

		result = iio_push_to_buffers_with_timestamp(indio_dev, data,
			timestamp);
		if (result)
			goto flush_fifo;
		fifo_count -= bytes_per_datum;
	}

end_session:
	mutex_unlock(&indio_dev->mlock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;

flush_fifo:

	inv_reset_fifo(indio_dev);
	mutex_unlock(&indio_dev->mlock);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}
