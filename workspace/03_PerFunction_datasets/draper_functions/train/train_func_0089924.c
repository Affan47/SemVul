srv_message(int argc, char **argv)
{
	struct stat  status;
	vaheader_t   header;
	char        *block;
	char        *msgname;
	int          fd;

	if ((!client_spool) || (!client_user) || (!(client_access & VBOXD_ACC_READ)))
	{
		message("%s Access denied (no read access).\r\n", VBOXD_VAL_ACCESSDENIED);

		return;
	}

	if (argc != 2)
	{
		message("%s usage: %s <message>\r\n", VBOXD_VAL_BADARGS, argv[0]);

		return;
	}

	if (chdir(client_spool) != 0)
	{
		message("%s Access denied (messagebox inaccessible).\r\n", VBOXD_VAL_ACCESSDENIED);

		return;
	}

	if (!(msgname = rindex(argv[1], '/')))
	{
		msgname = argv[1];
	}
	else msgname++;

	if ((fd = open(msgname, O_RDONLY)) != -1)
	{
		if (fstat(fd, &status) == 0)
		{
			if (header_get(fd, &header))
			{
				if (lseek(fd, 0, SEEK_SET) == 0)
				{
					if ((block = malloc(status.st_size)))
					{
						if (read(fd, block, status.st_size) == status.st_size)
						{
							message("%s %d\r\n", VBOXD_VAL_MESSAGE, status.st_size);
                                                        pullmsg(stdout);

							write(STDOUT_FILENO, block, status.st_size);

							message("%s .\r\n", VBOXD_VAL_MESSAGE);
							pullmsg(stdout);

							free(block);
						}
						else message("%s Can't read message (%s).\r\n", VBOXD_VAL_TEMPERROR, strerror(errno));
					}
					else message("%s Not enough memory (%s).\r\n", VBOXD_VAL_TEMPERROR, strerror(errno));
				}
				else message("%s Can't seek back (%s).\r\n", VBOXD_VAL_TEMPERROR, strerror(errno));
			}
			else message("%s Not a vbox message.\r\n", VBOXD_VAL_BADMESSAGE);
		}
		else message("%s Can't get message status (%s).\r\n", VBOXD_VAL_TEMPERROR, strerror(errno));

		close(fd);
	}
	else message("%s Can't open message (%s).\r\n", VBOXD_VAL_TEMPERROR, strerror(errno));
}
