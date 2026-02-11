gp2ap020a00f_thresh_event_handler(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct gp2ap020a00f_data *priv = iio_priv(indio_dev);
	u8 op_reg_flags, d0_reg_buf[2];
	unsigned int output_val, op_reg_val;
	int thresh_val_id, ret;


	ret = regmap_read(priv->regmap, GP2AP020A00F_OP_REG,
							&op_reg_val);
	if (ret < 0)
		goto done;

	op_reg_flags = op_reg_val & (GP2AP020A00F_FLAG_A | GP2AP020A00F_FLAG_P
					| GP2AP020A00F_PROX_DETECT);

	op_reg_val &= (~GP2AP020A00F_FLAG_A & ~GP2AP020A00F_FLAG_P
					& ~GP2AP020A00F_PROX_DETECT);


	if (priv->cur_opmode != GP2AP020A00F_OPMODE_PROX_DETECT) {
		ret = regmap_write(priv->regmap, GP2AP020A00F_OP_REG,
								op_reg_val);
		if (ret < 0)
			goto done;
	}

	if (op_reg_flags & GP2AP020A00F_FLAG_A) {


		ret = regmap_bulk_read(priv->regmap, GP2AP020A00F_D0_L_REG,
							d0_reg_buf, 2);
		if (ret < 0)
			goto done;

		output_val = le16_to_cpup((__le16 *)d0_reg_buf);

		if (gp2ap020a00f_adjust_lux_mode(priv, output_val))
			goto done;

		gp2ap020a00f_output_to_lux(priv, &output_val);


		if (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &priv->flags)) {
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TH_L_REG);
			if (output_val > priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_DIR_RISING),
				       iio_get_time_ns());
		}

		if (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &priv->flags)) {
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TL_L_REG);
			if (output_val < priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_DIR_FALLING),
				       iio_get_time_ns());
		}
	}

	if (priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_CLEAR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_IR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY) {
		set_bit(GP2AP020A00F_FLAG_DATA_READY, &priv->flags);
		wake_up(&priv->data_ready_queue);
		goto done;
	}

	if (test_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &priv->flags))

		irq_work_queue(&priv->work);

done:
	return IRQ_HANDLED;
}
