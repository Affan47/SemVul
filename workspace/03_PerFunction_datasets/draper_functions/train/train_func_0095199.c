find_action(struct input_event *ev, const char *buf)
{
	const char *action = NULL;
	int i;


	for (i = 0; i < n_evt; i++) {
		if (ev) {
			if (ev->type == evt_tab[i].n_type && ev->code == evt_tab[i].n_code && ev->value == evt_tab[i].value) {
				action = evt_tab[i].desc;
				break;
			}
		}

		if (buf) {
			if (strncmp(buf, evt_tab[i].desc, strlen(buf)) == 0) {
				action = evt_tab[i].desc;
				break;
			}
		}
	}


	if (action) {
		for (i = 0; i < n_act; i++) {
			if (strstr(action, act_tab[i].key)) {
				action = act_tab[i].action;
				break;
			}
		}
	}

	return action;
}
