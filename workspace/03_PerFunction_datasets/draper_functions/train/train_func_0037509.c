CHANreadtext(cp)
    register CHANNEL	*cp;
{
    register int	i;
    register BUFFER	*bp;
    char		*p;
    int			oerrno;


    bp = &cp->In;
    if (bp->Left <= LOW_WATER) {
	i = GROW_AMOUNT(bp->Size);
	bp->Size += i;
	bp->Left += i;
	RENEW(bp->Data, char, bp->Size);
    }


    bp->Left = bp->Size - bp->Used;
    i = read(cp->fd, &bp->Data[bp->Used],
	      (bp->Left - 1 > BUFSIZ ? BUFSIZ : bp->Left - 1));
    if (i < 0) {
#ifdef POLL_BUG

        if (errno == EAGAIN) {
            return -2;
        }
#endif
	oerrno = errno;
	p = CHANname(cp);
	errno = oerrno;
	syslog(L_ERROR, "%s cant read %m", p);
	return -1;
    }
    if (i == 0) {
	p = CHANname(cp);
	syslog(L_NOTICE, "%s readclose", p);
	return 0;
    }

    bp->Used += i;
    bp->Left -= i;
    return i;
}
