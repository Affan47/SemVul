set_dir_entries(char *directory, int (*set_fct)(const char *, const char *))
{
	struct dirent *eptr;
	DIR *dptr;

	if (directory != NULL)
	{
		if ((dptr = opendir(directory)) != NULL)
		{
			while ((eptr = readdir(dptr)) != NULL)
			{
				if (eptr->d_name[0] != '.')
				{
					if (set_fct(directory,eptr->d_name))
                                                return(UNKNOWN);
				}
			}

			closedir(dptr);
		}
		else
		{
			print_msg(PRT_ERR, "isdnrep: can't open directory `%s': %s!\n", directory, strerror(errno));
                        return(UNKNOWN);
		}
	}

	return 0;
}
