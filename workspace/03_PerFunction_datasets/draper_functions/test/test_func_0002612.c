perl_auto_load_from_path (const char *path)
{
	DIR *dir;
	struct dirent *ent;

	dir = opendir (path);
	if (dir) {
		while ((ent = readdir (dir))) {
			int len = strlen (ent->d_name);
			if (len > 3 && strcasecmp (".pl", ent->d_name + len - 3) == 0) {
				char *file = malloc (len + strlen (path) + 2);
				sprintf (file, "%s/%s", path, ent->d_name);
				perl_load_file (file);
				free (file);
			}
		}
		closedir (dir);
	}
}
