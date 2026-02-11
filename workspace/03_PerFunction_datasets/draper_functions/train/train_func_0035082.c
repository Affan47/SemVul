psql_start_test(const char *testname,
				_stringlist ** resultfiles,
				_stringlist ** expectfiles,
				_stringlist ** tags)
{
	PID_TYPE	pid;
	char		infile[MAXPGPATH];
	char		outfile[MAXPGPATH];
	char		expectfile[MAXPGPATH];
	char		psql_cmd[MAXPGPATH * 3];

	snprintf(infile, sizeof(infile), "%s/sql/%s.sql",
			 inputdir, testname);
	snprintf(outfile, sizeof(outfile), "%s/results/%s.out",
			 outputdir, testname);
	snprintf(expectfile, sizeof(expectfile), "%s/expected/%s.out",
			 inputdir, testname);

	add_stringlist_item(resultfiles, outfile);
	add_stringlist_item(expectfiles, expectfile);

	snprintf(psql_cmd, sizeof(psql_cmd),
			 SYSTEMQUOTE "\"%s%spsql\" -X -a -q -d \"%s\" < \"%s\" > \"%s\" 2>&1" SYSTEMQUOTE,
			 psqldir ? psqldir : "",
			 psqldir ? "/" : "",
			 dblist->str,
			 infile,
			 outfile);

	pid = spawn_process(psql_cmd);

	if (pid == INVALID_PID)
	{
		fprintf(stderr, _("could not start process for test %s\n"),
				testname);
		exit_nicely(2);
	}

	return pid;
}
