gdb_whatis(char *s)
{
	char buf[BUFSIZE], *p1;

	open_tmpfile();
        sprintf(buf, "whatis %s", s);
        if (!gdb_pass_through(buf, fp, GNU_RETURN_ON_ERROR)) {
		close_tmpfile();
		return FALSE;
	}

        rewind(pc->tmpfile);
        while (fgets(buf, BUFSIZE, pc->tmpfile)) {
		p1 = buf;
		if (STRNEQ(buf, "type = "))
			p1 += strlen("type = ");
		fprintf(pc->saved_fp, "%s", p1);
        }

	close_tmpfile();

	return TRUE;
}
