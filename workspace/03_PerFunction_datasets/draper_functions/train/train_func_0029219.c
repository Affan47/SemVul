acpi_update_hook(gpointer source, gpointer data)
{
	int action = 0;
	guint new, unread, unreadmarked, marked, total;
	guint replied, forwarded, locked, ignored, watched;

	if (alertpanel_blink_timeout_id)
		return FALSE;

	folder_count_total_msgs(&new, &unread, &unreadmarked, &marked, &total,
				&replied, &forwarded, &locked, &ignored, &watched);

	if (my_new != new || my_unread != unread) {
		my_new = new;
		my_unread = unread;
		if (my_new > 0) {
			action = acpiprefs.new_mail_action;
		} else if (my_unread > 0) {
			action = acpiprefs.unread_mail_action;
		} else {
			action = acpiprefs.no_mail_action;
		}

		if (action != my_action) {
			my_action = action;

			if (action != BLINK && blink_timeout_id != 0) {
				g_source_remove(blink_timeout_id);
				blink_timeout_id = 0;
			}

			switch (action) {
			case ON:
				acpi_set(TRUE);
				break;
			case BLINK:
				acpi_set(TRUE);
				last_blink = FALSE;
				blink_timeout_id = g_timeout_add(1000, acpi_blink, NULL);
				break;
			case OFF:
				acpi_set(FALSE);
				break;
			}
		}
	}

	return FALSE;
}
