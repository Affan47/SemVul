check_mail_maildir()
{
#ifndef NO_POSIX_SYSTEM
	int fd[2], pid;

	if (pipe(fd))
		return -1;

	if ((pid = fork()) < 0) {
		close(fd[0]);
		close(fd[1]);
		return -1;
	}

	if (!pid) {
		int d_new = 0, new = 0;
		char *s = NULL;
		struct dirent *d;
		DIR *dir;
		list_t l;

		close(fd[0]);

		for (l = mail_folders; l; l = l->next) {
			struct mail_folder *m = l->data;
			char *tmp = saprintf("%s/new", m->fname);

			if (!(dir = opendir(tmp))) {
				xfree(tmp);
				continue;
			}

			while ((d = readdir(dir))) {
				char *fname = saprintf("%s/%s", tmp, d->d_name);
				struct stat st;

				if (d->d_name[0] != '.' && !stat(fname, &st) && S_ISREG(st.st_mode))
					d_new++;

				xfree(fname);
			}

			xfree(tmp);
			closedir(dir);

			if (!l->next)
				s = saprintf("%d,%d", m->fhash, d_new);
			else
				s = saprintf("%d,%d\n", m->fhash, d_new);

			{
				int sent = 0, left = xstrlen(s);
				char *ptr = s;

				while (left > 0) {
					sent = write(fd[1], ptr, sizeof(ptr));

					if (sent == -1)
						break;

					left -= sent;
					ptr += sent;
				}
			}

			xfree(s);

			new += d_new;
			d_new = 0;
		}

		close(fd[1]);
		exit(0);
	}

	close(fd[1]);
	fcntl(fd[0], F_SETFL, O_NONBLOCK);

	watch_add_line(&mail_plugin, fd[0], WATCH_READ_LINE, mail_handler, NULL);


	return 0;
#else
	return -1;
#endif
}
