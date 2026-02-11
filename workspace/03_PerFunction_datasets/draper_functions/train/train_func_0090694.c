pm860x_init_charger(struct pm860x_charger_info *info)
{
	int ret;

	ret = pm860x_reg_read(info->i2c, PM8607_STATUS_2);
	if (ret < 0)
		return ret;

	mutex_lock(&info->lock);
	info->state = FSM_INIT;
	if (ret & STATUS2_CHG) {
		info->online = 1;
		info->allowed = 1;
	} else {
		info->online = 0;
		info->allowed = 0;
	}
	mutex_unlock(&info->lock);

	set_charging_fsm(info);
	return 0;
}
