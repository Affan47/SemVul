scan_recursively(build_store_t * data, char * dir) {

	int i, n;
	struct dirent ** ent;
	char path[MAXLEN];

	n = scandir(dir, &ent, filter, alphasort);
	for (i = 0; i < n; i++) {

		if (data->cancelled) {
			break;
		}

		snprintf(path, MAXLEN-1, "%s/%s", dir, ent[i]->d_name);

		if (is_dir(path)) {
			scan_recursively(data, path);
		} else {
			float d;

			set_prog_file_entry(data, path);
			set_prog_action_label(data, _("Reading file"));

			if (filter_excl_incl(data, path) && (d = get_file_duration(path)) > 0.0f) {
				process_track(data, path, ent[i]->d_name, d);
			}
		}

		free(ent[i]);
	}

	while (i < n) {
		free(ent[i]);
		++i;
	}

	if (n > 0) {
		free(ent);
	}
}
