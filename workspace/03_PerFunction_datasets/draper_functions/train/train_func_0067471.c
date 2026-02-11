connect_error(struct eb_aim_local_account_data *alad, char *msg)
{
	if (alad->login_activity_bar)
		ay_activity_bar_remove(alad->login_activity_bar);

	alad->login_activity_bar = 0;

	ay_do_error("AIM Error", msg);
}
