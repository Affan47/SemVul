snd_pcm_ladspa_check_dir(snd_pcm_ladspa_plugin_t * const plugin,
				    const char *path,
				    const char *label,
				    const unsigned long ladspa_id)
{
	DIR *dir;
	struct dirent * dirent;
	int len = strlen(path), err;
	int need_slash;
	char *filename;

	if (len < 1)
		return 0;
	need_slash = path[len - 1] != '/';

	dir = opendir(path);
	if (!dir)
		return -ENOENT;

	while (1) {
		dirent = readdir(dir);
		if (!dirent) {
			closedir(dir);
			return 0;
		}

		filename = malloc(len + strlen(dirent->d_name) + 1 + need_slash);
		if (filename == NULL) {
			closedir(dir);
			return -ENOMEM;
		}
		strcpy(filename, path);
		if (need_slash)
			strcat(filename, "/");
		strcat(filename, dirent->d_name);
		err = snd_pcm_ladspa_check_file(plugin, filename, label, ladspa_id);
		free(filename);
		if (err < 0 && err != -ENOENT) {
			closedir(dir);
			return err;
		}
		if (err > 0) {
			closedir(dir);
			return 1;
		}
	}

	return 0;
}
