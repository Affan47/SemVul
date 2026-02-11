modem_raw_read(char *line, int len)
{
#ifdef USE_NEW_MODEM_READER

	int use = 0;
	int i;

#ifdef DBG_NEW_MODEM_READER
	log(L_JUNK, "[READ] Function request %d byte(s) (now pos %d; len %d).\n", len, modem_input_pos, modem_input_len);
#endif

	if (len > MODEM_INPUT_LEN)
	{
		log(L_FATAL, "Internal modem buffer overflow (size %d; request %d)!\n", MODEM_INPUT_LEN, len);

		return(-1);
	}

	if (modem_input_len >= len)
	{
		memcpy(line, &modem_input[modem_input_pos], len);

		modem_input_len -= len;
		modem_input_pos += len;

#ifdef DBG_NEW_MODEM_READER
		log(L_JUNK, "[READ] Return all %d bytes (now pos %d; len %d).\n", len, modem_input_pos, modem_input_len);
#endif

		return(len);
	}

	if (modem_input_len > 0)
	{
		memcpy(line, &modem_input[modem_input_pos], modem_input_len);

#ifdef DBG_NEW_MODEM_READER
		log(L_JUNK, "[READ] Store %d of %d bytes (now pos 0; len 0).\n", modem_input_len, len);
#endif
	}
#ifdef DBG_NEW_MODEM_READER
	else log(L_JUNK, "[READ] Store nothing (pos 0; len 0).\n");
#endif

	len -= modem_input_len;
	use += modem_input_len;

	modem_input_pos = 0;
	modem_input_len = 0;

	if ((modem_input_len = read(setup.modem.fd, modem_input, MODEM_INPUT_LEN)) < 0)
	{
		modem_input_pos = 0;
		modem_input_len = 0;

#ifdef DBG_NEW_MODEM_READER
		log(L_JUNK, "[READ] Return only %d bytes (now pos %d; len %d).\n", use, modem_input_pos, modem_input_len);
#endif

		return(use);
	}

#ifdef DBG_NEW_MODEM_READER
	log(L_JUNK, "[READ] Read %d bytes (now pos %d; len %d).\n", modem_input_len, modem_input_pos, modem_input_len);
#endif

	for (i = 0; i < modem_input_len; i++)
	{
#ifdef DBG_NEW_MODEM_READER
		log_line(L_JUNK, "[READ] ");
		log_char(L_JUNK, modem_input[i]);
		log_text(L_JUNK, "\n");
#endif

		modem_check_nocarrier(modem_input[i]);
	}

	if (modem_input_len < len) len = modem_input_len;

	memcpy(&line[use], &modem_input[modem_input_pos], len);

	modem_input_len -= len;
	modem_input_pos += len;

#ifdef DBG_NEW_MODEM_READER
	log(L_JUNK, "[READ] Return %d bytes (now pos %d; len %d.\n", use + len, modem_input_pos, modem_input_len);
#endif

	return(use + len);

#else

	int r;
	int i;

	if ((r = read(setup.modem.fd, line, len)) > 0)
	{
		for (i = 0; i < r; i++)
		{
#ifdef DBG_OLD_MODEM_READER
			log_line(L_JUNK, "[OLDREAD] ");
			log_char(L_JUNK, line[i]);
			log_text(L_JUNK, "\n");
#endif

			modem_check_nocarrier(line[i]);
		}
	}

	return(r);

#endif
}
