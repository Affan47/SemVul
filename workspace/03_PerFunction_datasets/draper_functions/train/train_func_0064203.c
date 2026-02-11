ptyrecvbuf(buf, nbytes)
VOID_P buf;
int nbytes;
{
	char *cp;
	int len;

	cp = (char *)buf;
	if (ptyungetnum) {
		len = nbytes;
		if (len > ptyungetnum) len = ptyungetnum;
		memcpy(cp, (char *)ptyungetbuf, len * sizeof(u_char));
		cp += len;
		nbytes -= len;
		ptyungetnum -= len;
		memmove((char *)ptyungetbuf, (char *)&(ptyungetbuf[len]),
			ptyungetnum * sizeof(u_char));
	}

	return(recvbuf(emufd, cp, nbytes));
}
