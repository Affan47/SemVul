si476x_radio_change_func(struct si476x_radio *radio,
				    enum si476x_func func)
{
	int err;
	bool soft;


	if (func == radio->core->power_up_parameters.func)
		return 0;

	soft = true;
	err = si476x_core_stop(radio->core, soft);
	if (err < 0) {


		soft = false;
		err = si476x_core_stop(radio->core, soft);
		if (err < 0)
			return err;
	}


	radio->core->power_up_parameters.func = func;

	err = si476x_core_start(radio->core, soft);
	if (err < 0)
		return err;


	if (func != SI476X_FUNC_FM_RECEIVER &&
	    func != SI476X_FUNC_AM_RECEIVER)
		return err;

	return si476x_radio_do_post_powerup_init(radio, func);
}
