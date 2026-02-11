get_configure_options(char *gisbase)
{

    FILE *fp;
    char str[MAXSTR];

    if (strcmp(CONFIG_OPTS, "")) {

	return;
    }


    sprintf(str, "%s/etc/config.system", gisbase);
    fp = fopen(str, "r");
    if (fp == NULL) {
	print_warning
	    ("could not open %s for read access. Using default configure options.\n",
	     str);
	return;
    }


    if (nc_fgets_nb(str, MAXSTR, fp) != NULL) {
	strcpy(CONFIG_OPTS, str);
    }
}
