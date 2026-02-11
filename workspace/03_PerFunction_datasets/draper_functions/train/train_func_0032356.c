one_clicked (uint32_t which)
{
	if (buttons[which]->get_active()) {

		if (which != current_active) {
			uint32_t old = current_active;
			current_active = which;
			buttons[old]->set_active (false);
		}

	} else if (which == current_active) {


		gtk_idle_add (reactivate_button, buttons[which]);
	}
}
