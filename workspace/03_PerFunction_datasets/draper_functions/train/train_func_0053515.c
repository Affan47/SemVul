ssh_sftp_get_cmdline(char *prompt, int no_fds_ok)
{
    int ret;

    char* line = get_input_pushback();
    if (line != 0)
	return line;


    while (1) {
	ret = ssh_sftp_do_select(TRUE, no_fds_ok);
	if (ret < 0) {
	    printf("connection died\n");
	    return NULL;
	}
	if (ret > 0) {
	    int error = 0;
	    line = read_input_line(0, &error);
	    if (error)
		return NULL;

	    if (line == NULL)
		continue;

	    if (line[0] == '-')
	    {
		ProcessQuotaCmd(line);
		sfree(line);
	    }
	    else
		return line;
	}
    }
}
