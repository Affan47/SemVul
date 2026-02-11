da9063_poll_on(struct work_struct *work)
{
	struct da9063_onkey *onkey = container_of(work,
						struct da9063_onkey,
						work.work);
	const struct da906x_chip_config *config = onkey->config;
	unsigned int val;
	int fault_log = 0;
	bool poll = true;
	int error;


	error = regmap_read(onkey->regmap,
			    config->onkey_status,
			    &val);
	if (error) {
		dev_err(onkey->dev,
			"Failed to read ON status: %d\n", error);
		goto err_poll;
	}

	if (!(val & config->onkey_nonkey_mask)) {
		error = regmap_update_bits(onkey->regmap,
					   config->onkey_pwr_signalling,
					   config->onkey_nonkey_lock_mask,
					   0);
		if (error) {
			dev_err(onkey->dev,
				"Failed to reset the Key Delay %d\n", error);
			goto err_poll;
		}

		input_report_key(onkey->input, KEY_POWER, 0);
		input_sync(onkey->input);

		poll = false;
	}


	error = regmap_read(onkey->regmap,
			    config->onkey_fault_log,
			    &fault_log);
	if (error) {
		dev_warn(&onkey->input->dev,
			 "Cannot read FAULT_LOG: %d\n", error);
	} else if (fault_log & config->onkey_key_reset_mask) {
		error = regmap_write(onkey->regmap,
				     config->onkey_fault_log,
				     config->onkey_key_reset_mask);
		if (error) {
			dev_warn(&onkey->input->dev,
				 "Cannot reset KEY_RESET fault log: %d\n",
				 error);
		} else {


			dev_dbg(&onkey->input->dev,
				"Sending SHUTDOWN to DA9063 ...\n");
			error = regmap_write(onkey->regmap,
					     config->onkey_shutdown,
					     config->onkey_shutdown_mask);
			if (error)
				dev_err(&onkey->input->dev,
					"Cannot SHUTDOWN DA9063: %d\n",
					error);
		}
	}

err_poll:
	if (poll)
		schedule_delayed_work(&onkey->work, msecs_to_jiffies(50));
}
