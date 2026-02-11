filter_fix_linedirs (struct filter *chain)
{
	char   *buf;
	const int readsz = 512;
	int     lineno = 1;
	bool    in_gen = true;
	bool    last_was_blank = false;

	if (!chain)
		return 0;

	buf = (char *) flex_alloc (readsz);

	while (fgets (buf, readsz, stdin)) {

		regmatch_t m[10];


		if (buf[0] == '#'
		    && regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			int     num;
			char   *fname;


			num = regmatch_strtol (&m[1], buf, NULL, 0);
			fname = regmatch_dup (&m[2], buf);

			if (strcmp (fname,
				outfilename ? outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	headerfilename ? headerfilename : "<stdout>")
					== 0) {

				char    *s1, *s2;
				char	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				while ((s2 - filename) < (MAXLINE - 1) && *s1) {

					if (*s1 == '\\')
						*s2++ = '\\';

					if (*s1 == '\"')
						*s2++ = '\\';

					*s2++ = *s1++;
				}

				*s2 = '\0';


				in_gen = true;
				snprintf (buf, readsz, "#line %d \"%s\"\n",
					  lineno + 1, filename);
			}
			else {

				in_gen = false;
			}

			free (fname);
			last_was_blank = false;
		}


		else if (in_gen
			 && regexec (&regex_blank_line, buf, 0, NULL,
				     0) == 0) {
			if (last_was_blank)
				continue;
			else
				last_was_blank = true;
		}

		else {

			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	if (ferror (stdout))
		lerrsf (_("error writing output file %s"),
			outfilename ? outfilename : "<stdout>");

	else if (fclose (stdout))
		lerrsf (_("error closing output file %s"),
			outfilename ? outfilename : "<stdout>");

	return 0;
}
