find_idle_and_ttywrite(register WHERE *w) {
	struct stat sb;


	if (strchr(w->tty, ':')) {
		w->idletime = 0;
		w->writable = 0;
		return;
	}
	snprintf(tbuf, TBUFLEN, "%s/%s", _PATH_DEV, w->tty);
	if (stat(tbuf, &sb) < 0) {
		eprintf("finger: %s: %s\n", tbuf, strerror(errno));
		return;
	}
	w->idletime = now < sb.st_atime ? 0 : now - sb.st_atime;

#define	TALKABLE	0220
	w->writable = ((sb.st_mode & TALKABLE) == TALKABLE);
}
