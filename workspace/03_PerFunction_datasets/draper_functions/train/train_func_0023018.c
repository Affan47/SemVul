hts221_get_sensor_scale(struct hts221_hw *hw,
				   enum iio_chan_type ch_type,
				   int *val, int *val2)
{
	s64 tmp;
	s32 rem, div, data;

	switch (ch_type) {
	case IIO_HUMIDITYRELATIVE:
		data = hw->sensors[HTS221_SENSOR_H].slope;
		div = (1 << 4) * 1000;
		break;
	case IIO_TEMP:
		data = hw->sensors[HTS221_SENSOR_T].slope;
		div = (1 << 6) * 1000;
		break;
	default:
		return -EINVAL;
	}

	tmp = div_s64(data * 1000000000LL, div);
	tmp = div_s64_rem(tmp, 1000000000LL, &rem);

	*val = tmp;
	*val2 = rem;

	return IIO_VAL_INT_PLUS_NANO;
}
