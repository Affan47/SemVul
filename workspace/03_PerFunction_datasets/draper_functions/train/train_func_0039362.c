usb_tty(char *sys)
{
	char *base;
	int num_configs;
	int config;
	struct dirent **namelist;
	int interface;
	int num_interfaces;
	char endpoint_base[20];
	char *endpoint_full;
	char *tty_dir;
	int ntty;
	char *tty;

	base = cc_basename(sys);
	num_configs = load_hex(sys, "bNumConfigurations");
	num_interfaces = load_hex(sys, "bNumInterfaces");
	for (config = 1; config <= num_configs; config++) {
		for (interface = 0; interface < num_interfaces; interface++) {
			sprintf(endpoint_base, "%s:%d.%d",
				base, config, interface);
			endpoint_full = cc_fullname(sys, endpoint_base);


			ntty = scandir(endpoint_full, &namelist,
				       dir_filter_tty_colon,
				       alphasort);
			if (ntty > 0) {
				free(endpoint_full);
				tty = cc_fullname("/dev", namelist[0]->d_name + 4);
				free(namelist);
				return tty;
			}


			tty_dir = cc_fullname(endpoint_full, "tty");
			ntty = scandir(tty_dir, &namelist,
				       dir_filter_tty,
				       alphasort);
			free (tty_dir);
			if (ntty > 0) {
				tty = cc_fullname("/dev", namelist[0]->d_name);
				free(endpoint_full);
				free(namelist);
				return tty;
			}


			ntty = scandir(endpoint_full, &namelist,
				       dir_filter_tty,
				       alphasort);
			free(endpoint_full);
			if (ntty > 0) {
				tty = cc_fullname("/dev", namelist[0]->d_name);
				free(namelist);
				return tty;
			}
		}
	}
	return NULL;
}
