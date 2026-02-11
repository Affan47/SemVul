bq24257_handle_state_change(struct bq24257_device *bq,
					struct bq24257_state *new_state)
{
	int ret;
	struct bq24257_state old_state;

	mutex_lock(&bq->lock);
	old_state = bq->state;
	mutex_unlock(&bq->lock);


	if (!new_state->power_good) {
		dev_dbg(bq->dev, "Power removed\n");
		if (bq->iilimit_autoset_enable) {
			cancel_delayed_work_sync(&bq->iilimit_setup_work);


			ret = bq24257_field_write(bq, F_DPDM_EN, 1);
			if (ret < 0)
				goto error;
		}


		ret = bq24257_field_write(bq, F_IILIMIT, bq->init_data.iilimit);
		if (ret < 0)
			goto error;
	} else if (!old_state.power_good) {
		dev_dbg(bq->dev, "Power inserted\n");

		if (bq->iilimit_autoset_enable)

			schedule_delayed_work(&bq->iilimit_setup_work,
				      msecs_to_jiffies(BQ24257_ILIM_SET_DELAY));
	} else if (new_state->fault == FAULT_NO_BAT) {
		dev_warn(bq->dev, "Battery removed\n");
	} else if (new_state->fault == FAULT_TIMER) {
		dev_err(bq->dev, "Safety timer expired! Battery dead?\n");
	}

	return;

error:
	dev_err(bq->dev, "%s: Error communicating with the chip.\n", __func__);
}
