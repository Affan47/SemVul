exec_data (GIOChannel *source, GIOCondition condition, struct nbexec *s)
{
	char *buf, *readpos, *rest;
	int rd, len;
	int sok = s->myfd;

	len = s->buffill;
	if (len) {

		buf = malloc(len + 2050);
		memcpy(buf, s->linebuf, len);
		readpos = buf + len;
		free(s->linebuf);
		s->linebuf = NULL;
	}
	else
		readpos = buf = malloc(2050);

	rd = read (sok, readpos, 2048);
	if (rd < 1)
	{

		kill(s->childpid, SIGKILL);
		if (len) {
			buf[len] = '\0';
			exec_handle_colors(buf, len);
			if (s->tochannel)
			{

				unsigned int old = prefs.hex_completion_auto;
				prefs.hex_completion_auto = 0;
				handle_multiline (s->sess, buf, FALSE, TRUE);
				prefs.hex_completion_auto = old;
			}
			else
				PrintText (s->sess, buf);
		}
		free(buf);
		waitpid (s->childpid, NULL, 0);
		s->sess->running_exec = NULL;
		fe_input_remove (s->iotag);
		close (sok);
		free (s);
		return TRUE;
	}
	len += rd;
	buf[len] = '\0';

	rest = memrchr(buf, '\n', len);
	if (rest)
		rest++;
	else
		rest = buf;
	if (*rest) {
		s->buffill = len - (rest - buf);
		s->linebuf = malloc(s->buffill + 1);
		memcpy(s->linebuf, rest, s->buffill);
		*rest = '\0';
		len -= s->buffill;
	}
	else
		s->buffill = 0;

	if (len) {
		exec_handle_colors (buf, len);
		if (s->tochannel)
			handle_multiline (s->sess, buf, FALSE, TRUE);
		else
			PrintText (s->sess, buf);
	}

	free(buf);
	return TRUE;
}
