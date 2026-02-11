eb_sign_off_all()
{
	LList *node = accounts;
	while (node) {
		eb_local_account *ac = (eb_local_account *)(node->data);
		if (ac && ac->connected) {
			char buff[1024];

			RUN_SERVICE(ac)->logout(ac);
			snprintf(buff, 1024, _("Setting %s (on %s) to Offline"),
				ac->handle, get_service_name(ac->service_id));

			update_status_message(buff);
		}

		if (ac && ac->mgmt_flush_tag) {
			eb_timeout_remove(ac->mgmt_flush_tag);
			ac->mgmt_flush_tag = 0;
		}
		node = node->next;
	}
	set_menu_sensitivity();
}
