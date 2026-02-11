streamio_open(char *name)
{
	struct stat status;

	streamio_t	*streamio;
	char			*file;
	char			*save;
	long			 i;
	int			 fd;

	if ((fd = open(name, O_RDONLY)) != -1)
	{
		if (stat(name, &status) == 0)
		{
			if ((streamio = malloc(sizeof(streamio_t))))
			{
				if ((file = malloc(status.st_size + 3)))
				{
					if ((save = malloc(strlen(name) + 1)))
					{
						xstrncpy(save, name, strlen(name));

						if (read(fd, file, status.st_size) == status.st_size)
						{
							file[status.st_size + 0] = 1;
							file[status.st_size + 1] = 1;
							file[status.st_size + 2] = 1;

							for (i = 0; i < status.st_size; i++)
							{
								if (file[i] == 13) file[i] = 32;
								if (file[i] == 10) file[i] = 0;
							}

							streamio->fd	= fd;
							streamio->name	= save;
							streamio->file	= file;
							streamio->next	= file;
							streamio->time	= status.st_mtime;
							streamio->line	= 0;

							return(streamio);
						}

						free(save);
					}

					free(file);
				}

				free(streamio);
			}
		}

		close(fd);
	}

	return(NULL);
}
