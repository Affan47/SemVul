start_autovbox(int compression, char *name, char *id, char *phone, char *location)
{
	vaheader_t	header;
	int	      result;

	vboxtmpfile = NULL;

	signal(SIGINT , leave_autovbox);
	signal(SIGQUIT, leave_autovbox);
	signal(SIGTERM, leave_autovbox);
	signal(SIGHUP , leave_autovbox);
	signal(SIGPIPE, leave_autovbox);

	if (!(vboxtmpfile = tmpfile()))
	{
		sprintf(perrormsg, "%s: can't create tmpfile", vbasename);
		perror(perrormsg);
		leave_autovbox(255);
	}

	xstrncpy(header.magic	, VAH_MAGIC	, VAH_MAX_MAGIC	);
	xstrncpy(header.callerid, id			, VAH_MAX_CALLERID);
	xstrncpy(header.name		, name		, VAH_MAX_NAME		);
	xstrncpy(header.phone	, phone		, VAH_MAX_PHONE	);
	xstrncpy(header.location, location	, VAH_MAX_LOCATION);

	header.time				= htonl(time(NULL));
	header.compression	= htonl(compression);

	if (fwrite(&header, sizeof(vaheader_t), 1, stdout) != 1)
	{
		fprintf(stderr, "%s: can't write vbox audio header.\n", vbasename);

		leave_autovbox(255);
	}

	result = convert_au_to_pvf(stdin, vboxtmpfile);

	if (result == 0)
	{
		result = 255;

		switch (compression)
		{
			case 2:
			case 3:
			case 4:
				result = convert_pvf_to_adpcm(compression, vboxtmpfile, stdout);
				break;

			case 6:
				result = convert_pvf_to_ulaw(vboxtmpfile, stdout);
				break;

			default:
				fprintf(stderr, "%s: unsupported compression type.\n", vbasename);
				break;

		}
	}

	leave_autovbox(result);
}
