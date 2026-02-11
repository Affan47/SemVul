faim_cb_connerr(aim_session_t *sess, aim_frame_t *fr, ...)
{
	eb_local_account *ela = (eb_local_account *)sess->aux_data;
	struct eb_aim_local_account_data *alad =
		(struct eb_aim_local_account_data *)ela->
		protocol_local_account_data;

	va_list ap;
	fu16_t code;
	char *msg;

	va_start(ap, fr);
	code = (fu16_t) va_arg(ap, int);
	msg = va_arg(ap, char *);
	va_end(ap);

	LOG(("Disconnected.  Code is 0x%04x and msg is %s\n", code, msg))

		if ((fr) && (fr->conn) && (fr->conn->type == AIM_CONN_TYPE_BOS)) {
		if (code == 0x0001) {
			connect_error(alad,
				"You have been disconnected because you have signed on with this screen name at another location.");
		} else {
			connect_error(alad,
				"You have been signed off for an unknown reason.");
		}

		is_setting_state = 1;
		if (ela->status_menu) {
			eb_set_active_menu_status(ela->status_menu,
				AIM_OFFLINE);
		}
		is_setting_state = 0;
	}

	return 1;
}
