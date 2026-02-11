ay_aim_get_status_string(eb_account *account)
{
	static gchar string[255], buf[255];
	struct eb_aim_account_data *aad =
		(struct eb_aim_account_data *)account->protocol_account_data;
	strcpy(buf, "");
	strcpy(string, "");

	if (aad->idle_time) {
		int hours, minutes, days;
		minutes = aad->idle_time;
		hours = minutes / 60;
		minutes = minutes % 60;
		days = hours / 24;
		hours = hours % 24;
		if (days) {
			g_snprintf(buf, 255, " %d:%02d:%02d", days, hours,
				minutes);
		} else if (hours) {
			g_snprintf(buf, 255, " %d:%02d", hours, minutes);
		} else {
			g_snprintf(buf, 255, " %d", minutes);
		}
	}

	if (aad->evil)
		g_snprintf(string, 255, "[%d%%]%s", aad->evil, buf);
	else
		g_snprintf(string, 255, "%s", buf);

	if (!account->online)
		g_snprintf(string, 255, "Offline");

	return string;
}
