gp2ap020a00f_read_event_val(struct iio_dev *indio_dev,
				       const struct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_direction dir,
				       enum iio_event_info info,
				       int *val, int *val2)
{
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	u8 thresh_reg_l;
	int err = IIO_VAL_INT;

	mutex_lock(&data->lock);

	thresh_reg_l = gp2ap020a00f_get_thresh_reg(chan, dir);

	if (thresh_reg_l > GP2AP020A00F_PH_L_REG) {
		err = -EINVAL;
		goto error_unlock;
	}

	*val = data->thresh_val[GP2AP020A00F_THRESH_VAL_ID(thresh_reg_l)];

error_unlock:
	mutex_unlock(&data->lock);

	return err;
}
