imap_append0(struct mailbox *mp, const char *name, FILE *fp)
{
	char	*buf, *bp, *lp;
	size_t	bufsize, buflen, count;
	off_t	off1 = -1, offs;
	int	inhead = 1;
	int	flag = MNEW|MNEWEST;
	long	size = 0;
	time_t	tim;
	enum okay	ok;

	buf = smalloc(bufsize = LINESIZE);
	buflen = 0;
	count = fsize(fp);
	offs = ftell(fp);
	time(&tim);
	do {
		bp = fgetline(&buf, &bufsize, &count, &buflen, fp, 1);
		if (bp == NULL || strncmp(buf, "From ", 5) == 0) {
			if (off1 != (off_t)-1) {
				ok=imap_append1(mp, name, fp, off1,
						size, flag, tim);
				if (ok == STOP)
					return STOP;
				fseek(fp, offs+buflen, SEEK_SET);
			}
			off1 = offs + buflen;
			size = 0;
			inhead = 1;
			flag = MNEW;
			if (bp != NULL)
				tim = unixtime(buf);
		} else
			size += buflen+1;
		offs += buflen;
		if (bp && buf[0] == '\n')
			inhead = 0;
		else if (bp && inhead && ascncasecmp(buf, "status", 6) == 0) {
			lp = &buf[6];
			while (whitechar(*lp&0377))
				lp++;
			if (*lp == ':')
				while (*++lp != '\0')
					switch (*lp) {
					case 'R':
						flag |= MREAD;
						break;
					case 'O':
						flag &= ~MNEW;
						break;
					}
		} else if (bp && inhead &&
				ascncasecmp(buf, "x-status", 8) == 0) {
			lp = &buf[8];
			while (whitechar(*lp&0377))
				lp++;
			if (*lp == ':')
				while (*++lp != '\0')
					switch (*lp) {
					case 'F':
						flag |= MFLAGGED;
						break;
					case 'A':
						flag |= MANSWERED;
						break;
					case 'T':
						flag |= MDRAFTED;
						break;
					}
		}
	} while (bp != NULL);
	free(buf);
	return OKAY;
}
