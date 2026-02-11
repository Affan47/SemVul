buffer_pwrite(int n, char *s, unsigned len)
{
	int i;
	struct logdir *ld = &dir[n];

	if (ld->sizemax) {
		if (ld->size >= ld->sizemax)
			rotate(ld);
		if (len > (ld->sizemax - ld->size))
			len = ld->sizemax - ld->size;
	}
	while (1) {


		i = fwrite(s, 1, len, ld->filecur);
		if (i == len) break;

		if ((errno == ENOSPC) && (ld->nmin < ld->nmax)) {
			DIR *d;
			struct dirent *f;
			char oldest[FMT_PTIME];
			int j = 0;

			while (fchdir(ld->fddir) == -1)
				pause2cannot("change directory, want remove old logfile",
							 ld->name);
			oldest[0] = 'A';
			oldest[1] = oldest[27] = '\0';
			while (!(d = opendir(".")))
				pause2cannot("open directory, want remove old logfile",
							 ld->name);
			errno = 0;
			while ((f = readdir(d)))
				if ((f->d_name[0] == '@') && (strlen(f->d_name) == 27)) {
					++j;
					if (strcmp(f->d_name, oldest) < 0)
						memcpy(oldest, f->d_name, 27);
				}
			if (errno) warn2("can't read directory, want remove old logfile",
					ld->name);
			closedir(d);
			errno = ENOSPC;
			if (j > ld->nmin) {
				if (*oldest == '@') {
					bb_error_msg(WARNING"out of disk space, delete: %s/%s",
							ld->name, oldest);
					errno = 0;
					if (unlink(oldest) == -1) {
						warn2("can't unlink oldest logfile", ld->name);
						errno = ENOSPC;
					}
					while (fchdir(fdwdir) == -1)
						pause1cannot("change to initial working directory");
				}
			}
		}
		if (errno)
			pause2cannot("write to current", ld->name);
	}

	ld->size += i;
	if (ld->sizemax)
		if (s[i-1] == '\n')
			if (ld->size >= (ld->sizemax - linemax))
				rotate(ld);
	return i;
}
