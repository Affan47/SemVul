rmtree(const char *path, bool rmtopdir)
{
	bool		result = true;
	char		pathbuf[MAXPGPATH];
	char	  **filenames;
	char	  **filename;
	struct stat statbuf;


	filenames = pgfnames(path);

	if (filenames == NULL)
		return false;


	for (filename = filenames; *filename; filename++)
	{
		snprintf(pathbuf, MAXPGPATH, "%s/%s", path, *filename);


		if (lstat(pathbuf, &statbuf) != 0)
		{
			if (errno != ENOENT)
			{
#ifndef FRONTEND
				elog(WARNING, "could not stat file or directory \"%s\": %m",
					 pathbuf);
#else
				fprintf(stderr, _("could not stat file or directory \"%s\": %s\n"),
						pathbuf, strerror(errno));
#endif
				result = false;
			}
			continue;
		}

		if (S_ISDIR(statbuf.st_mode))
		{

			if (!rmtree(pathbuf, true))
			{

				result = false;
			}
		}
		else
		{
			if (unlink(pathbuf) != 0)
			{
				if (errno != ENOENT)
				{
#ifndef FRONTEND
					elog(WARNING, "could not remove file or directory \"%s\": %m",
						 pathbuf);
#else
					fprintf(stderr, _("could not remove file or directory \"%s\": %s\n"),
							pathbuf, strerror(errno));
#endif
					result = false;
				}
			}
		}
	}

	if (rmtopdir)
	{
		if (rmdir(path) != 0)
		{
#ifndef FRONTEND
			elog(WARNING, "could not remove file or directory \"%s\": %m",
				 path);
#else
			fprintf(stderr, _("could not remove file or directory \"%s\": %s\n"),
					path, strerror(errno));
#endif
			result = false;
		}
	}

	pgfnames_cleanup(filenames);

	return result;
}
