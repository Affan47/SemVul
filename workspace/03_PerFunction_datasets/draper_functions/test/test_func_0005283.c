read_config(char* filename)
{
	FILE* fp = NULL;
	char buffer[256];

	char* bufp = NULL;
	char* opt = NULL;
	char* optdata = NULL;

	if ((fp = fopen(filename, "r")) != NULL)
	{

		while (!feof(fp))
		{
			if (fgets(buffer, 256, fp))
			{
				bufp = trim(buffer);


				if(bufp[0] == '#' || bufp[0] == ';' || bufp[0] == '[')
					continue;


				opt = strtok(bufp, "=");
				if (opt)
				{
					opt = trim(opt);
					optdata = strtok(NULL, "=");

					if (optdata)
					{
						optdata = trim(optdata);

						if (!strcmp(opt, "daemonize"))
						{
							option_daemonize = atoi(optdata);
						}
						else if (!strcmp(opt, "port"))
						{
							listen_port = atoi(optdata);
						}
						else if (!strcmp(opt, "device"))
						{
							serial_device_name = strdup(optdata);
						}
						else if (!strcmp(opt, "bind_ip"))
						{
							option_bind_ip = strdup(optdata);
						}
						else if (!strcmp(opt, "baudrate"))
						{
							option_baud_rate = strdup(optdata);
						}
						else if (!strcmp(opt, "raw_device_mode"))
						{
							option_raw_device_mode = atoi(optdata);
						}
						else if (!strcmp(opt, "send_terminal_init"))
						{
							option_send_terminal_init = atoi(optdata);
						}
						else if (!strcmp(opt, "preserve_connections"))
						{
							option_keep_connection = atoi(optdata);
						}
						else if (!strcmp(opt, "device_open_delay"))
						{
							option_open_serial_delay = atoi(optdata);
						}
						else if (!strcmp(opt, "pid_file"))
						{
							option_pid_file = strdup(optdata);
						}
#ifdef HAVE_LIBSSL
						else if (!strcmp(opt, "encrypted"))
						{
							option_ssl = atoi(optdata);
						}
						else if (!strcmp(opt, "ca_certificate"))
						{
							option_ca_certificate = strdup(optdata);
						}
						else if (!strcmp(opt, "ssl_certificate"))
						{
							option_ssl_certificate = strdup(optdata);
						}
						else if (!strcmp(opt, "ssl_key"))
						{
							option_ssl_key = strdup(optdata);
						}
						else if (!strcmp(opt, "ssl_crl"))
						{
							option_ssl_crl = strdup(optdata);
						}
#endif
					}
				}
			}
		}

		fclose(fp);

		return TRUE;
	}

	return FALSE;
}
