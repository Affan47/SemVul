read_configuration(void)
{
    PRIV_ROOT_START
    file = fopen(CFINGERD_CONF, "r");
    PRIV_ROOT_END

    trusted_host_num = rejected_host_num = fakeuser_num = num_finger_sites = 0;
    forward_host_num = 0;
    num_headers = 1;

    if (file)
	while(!feof(file)) {
	    char *line, ch = fgetc(file);


	    if (ch == EOF)
		break;

	    ungetc(ch, file);
	    line = (char *) malloc(80);
	    if ((ch != '#') && (ch != '\'')) {
		fgets(line, 80, file);
		if (!(strncasecmp(line, "FILES ", 6))) {
		    do_files(line);
		} else if (!(strncasecmp(line, "HOSTS ", 6))) {
		    do_hosts(line);
		} else if (!(strncasecmp(line, "CONFIG ", 7))) {
		    do_config(line);
		}
	    } else
		fgets(line, 80, file);

	    free(line);
	}
    else {
	printf("No cfingerd.conf file present.  Check your setup.\n");
	exit(1);
    }
}
