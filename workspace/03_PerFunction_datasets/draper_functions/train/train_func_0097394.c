windows_save() {
	window_t *w;

	if (config_windows_save) {
		string_t s = string_init(NULL);
		int maxid = 0, i;

		for (w = windows; w; w = w->next) {
			if (!w->floating && w->id > maxid)
				maxid = w->id;
		}

		for (i = 1; i <= maxid; i++) {
			const char *target = "-";
			const char *session_name = NULL;

			for (w = windows; w; w = w->next) {
				if (w->id == i) {
					target = w->target;
					if (w->session)
						session_name = w->session->uid;
					break;
				}
			}

			if (session_name && target) {
				string_append(s, session_name);
				string_append_c(s, '/');
			}

			if (target) {
				string_append_c(s, '\"');
				string_append(s, target);
				string_append_c(s, '\"');
			}

			if (i < maxid)
				string_append_c(s, '|');
		}

		for (w = windows; w; w = w->next) {
			if (w->floating && (!w->target || xstrncmp(w->target, "__", 2))) {
				char *tmp = saprintf("|*%d,%d,%d,%d,%d,%s", w->left, w->top, w->width, w->height, w->frames, w->target);
				string_append(s, tmp);
				xfree(tmp);
			}
		}
		xfree(config_windows_layout);
		config_windows_layout = string_free(s, 0);
	}
}
