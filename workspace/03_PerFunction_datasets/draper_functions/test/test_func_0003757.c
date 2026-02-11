writefile(char *path, char **lines)
{
	FILE	   *out_file;
	char	  **line;

	if ((out_file = fopen(path, "w")) == NULL)
	{
		fprintf(stderr, _("%s: could not open file \"%s\" for writing: %s\n"),
				progname, path, strerror(errno));
		exit_nicely();
	}
	for (line = lines; *line != NULL; line++)
	{
		if (fputs(*line, out_file) < 0)
		{
			fprintf(stderr, _("%s: could not write file \"%s\": %s\n"),
					progname, path, strerror(errno));
			exit_nicely();
		}
		free(*line);
	}
	if (fclose(out_file))
	{
		fprintf(stderr, _("%s: could not write file \"%s\": %s\n"),
				progname, path, strerror(errno));
		exit_nicely();
	}
}
