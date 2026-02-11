da9150_gpadc_read_scale(int channel, int *val, int *val2)
{
	switch (channel) {
	case DA9150_GPADC_CHAN_VBAT:
		*val = 2932;
		*val2 = 1000;
		return IIO_VAL_FRACTIONAL;
	case DA9150_GPADC_CHAN_TJUNC_CORE:
	case DA9150_GPADC_CHAN_TJUNC_OVP:
		*val = 1000000;
		*val2 = 4420;
		return IIO_VAL_FRACTIONAL;
	default:
		return -EINVAL;
	}
}
