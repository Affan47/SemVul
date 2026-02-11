start_vboxtoau(int samplemode, int samplerate)
{
	vaheader_t	header;
	int	      compression;
	int 	      result;

	vboxtmpfile = NULL;

	signal(SIGINT , leave_vboxtoau);
	signal(SIGQUIT, leave_vboxtoau);
	signal(SIGTERM, leave_vboxtoau);
	signal(SIGHUP , leave_vboxtoau);
	signal(SIGPIPE, leave_vboxtoau);

	if (!(vboxtmpfile = tmpfile()))
	{
		sprintf(perrormsg, "%s: can't create tmpfile", vbasename);
		perror(perrormsg);
		leave_vboxtoau(255);
	}

	if (fread(&header, sizeof(vaheader_t), 1, stdin) != 1)
	{
		sprintf(perrormsg, "%s: can't read vbox audio header", vbasename);
		perror(perrormsg);
		leave_vboxtoau(255);
	}

	if (strncmp(header.magic, VAH_MAGIC, VAH_MAX_MAGIC) != 0)
	{
		fprintf(stderr, "%s: sample contains no vbox audio header.\n", vbasename);

		leave_vboxtoau(255);
	}

	compression = (int)ntohl(header.compression);

	result = 255;

	switch (compression)
	{
		case 2:
		case 3:
		case 4:
			result = convert_adpcm_to_pvf(compression, stdin, vboxtmpfile);
			break;

		case 6:
			result = convert_ulaw_to_pvf(stdin, vboxtmpfile);
			break;

		default:
			fprintf(stderr, "%s: unknown/unsupported compression %d.\n", vbasename, compression);
			break;
	}

	if (result == 0)
	{
		result = convert_pvf_to_au(samplemode, samplerate, vboxtmpfile, stdout);
	}

	leave_vboxtoau(result);
}
