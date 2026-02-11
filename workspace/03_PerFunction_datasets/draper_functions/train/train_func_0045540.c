results_differ(const char *testname, const char *resultsfile, const char *default_expectfile)
{
	char		expectfile[MAXPGPATH];
	char		diff[MAXPGPATH];
	char		cmd[MAXPGPATH * 3];
	char		best_expect_file[MAXPGPATH];
	FILE	   *difffile;
	int			best_line_count;
	int			i;
	int			l;
	const char *platform_expectfile;


	platform_expectfile = get_expectfile(testname, resultsfile);

	strlcpy(expectfile, default_expectfile, sizeof(expectfile));
	if (platform_expectfile)
	{


		char	   *p = strrchr(expectfile, '/');

		if (p)
			strcpy(++p, platform_expectfile);
	}


	snprintf(diff, sizeof(diff), "%s.diff", resultsfile);


	snprintf(cmd, sizeof(cmd),
			 "diff %s \"%s\" \"%s\" > \"%s\"",
			 basic_diff_opts, expectfile, resultsfile, diff);


	if (run_diff(cmd, diff) == 0)
	{
		unlink(diff);
		return false;
	}


	best_line_count = file_line_count(diff);
	strcpy(best_expect_file, expectfile);

	for (i = 0; i <= 9; i++)
	{
		char	   *alt_expectfile;

		alt_expectfile = get_alternative_expectfile(expectfile, i);
		if (!alt_expectfile)
		{
			fprintf(stderr, _("Unable to check secondary comparison files: %s\n"),
					strerror(errno));
			exit(2);
		}

		if (!file_exists(alt_expectfile))
		{
			free(alt_expectfile);
			continue;
		}

		snprintf(cmd, sizeof(cmd),
				 "diff %s \"%s\" \"%s\" > \"%s\"",
				 basic_diff_opts, alt_expectfile, resultsfile, diff);

		if (run_diff(cmd, diff) == 0)
		{
			unlink(diff);
			free(alt_expectfile);
			return false;
		}

		l = file_line_count(diff);
		if (l < best_line_count)
		{

			best_line_count = l;
			strlcpy(best_expect_file, alt_expectfile, sizeof(best_expect_file));
		}
		free(alt_expectfile);
	}


	if (platform_expectfile)
	{
		snprintf(cmd, sizeof(cmd),
				 "diff %s \"%s\" \"%s\" > \"%s\"",
				 basic_diff_opts, default_expectfile, resultsfile, diff);

		if (run_diff(cmd, diff) == 0)
		{

			unlink(diff);
			return false;
		}

		l = file_line_count(diff);
		if (l < best_line_count)
		{

			best_line_count = l;
			strlcpy(best_expect_file, default_expectfile, sizeof(best_expect_file));
		}
	}


	snprintf(cmd, sizeof(cmd),
			 "diff %s \"%s\" \"%s\" >> \"%s\"",
			 pretty_diff_opts, best_expect_file, resultsfile, difffilename);
	run_diff(cmd, difffilename);


	difffile = fopen(difffilename, "a");
	if (difffile)
	{
		fprintf(difffile,
				"\n======================================================================\n\n");
		fclose(difffile);
	}

	unlink(diff);
	return true;
}
