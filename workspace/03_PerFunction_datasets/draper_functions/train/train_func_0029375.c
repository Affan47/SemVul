writeback(FILE *res, FILE *obuf)
{
	struct message *mp;
	int p, c;

	p = 0;
	fseek(obuf, 0L, SEEK_SET);
#ifndef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
			putc(c, obuf);
#endif
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if ((mp->m_flag&MPRESERVE)||(mp->m_flag&MTOUCH)==0) {
			p++;
			if (send(mp, obuf, NULL, NULL, SEND_MBOX, NULL) < 0) {
				perror(mailname);
				fseek(obuf, 0L, SEEK_SET);
				return(-1);
			}
		}
#ifdef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
			putc(c, obuf);
#endif
	fflush(obuf);
	trunc(obuf);
	if (ferror(obuf)) {
		perror(mailname);
		fseek(obuf, 0L, SEEK_SET);
		return(-1);
	}
	if (res != NULL)
		Fclose(res);
	fseek(obuf, 0L, SEEK_SET);
	alter(mailname);
	if (p == 1)
		printf(catgets(catd, CATSET, 155,
				"Held 1 message in %s\n"), mailname);
	else
		printf(catgets(catd, CATSET, 156,
				"Held %d messages in %s\n"), p, mailname);
	return(0);
}
