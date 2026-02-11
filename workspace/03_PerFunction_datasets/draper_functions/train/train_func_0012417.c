_ahci_em_messages(const char *path)
{


	char buf[PATH_MAX];
	char *link, *name;
	DIR *dh;
	struct dirent *de = NULL;


	if (get_int(path, 0, "driver/module/parameters/ahci_em_messages") != 0)
		return 1;

	if (!get_int("", 0, "sys/module/libahci/parameters/ahci_em_messages"))
		return 0;

	if (snprintf(buf, sizeof(buf), "%s/%s", path, "driver") < 0)
		return 0;

	link = realpath(buf, NULL);
	if (!link)
		return 0;

	name = strrchr(link, '/');
	if (!name++) {
		free(link);
		return 0;
	}


	dh = opendir("/sys/module/libahci/holders");
	if (dh) {


		while ((de = readdir(dh))) {
			if (!strcmp(de->d_name, name))
				break;
		}
		closedir(dh);
		free(link);
		return de ? 1 : 0;
	} else {
		free(link);
		return 1;
	}
}
