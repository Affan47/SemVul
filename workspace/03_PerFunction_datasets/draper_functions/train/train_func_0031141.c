awaken(Pool *p)
{
    p->flags &= ~PF_ASLEEP;
    timerclear(&p->awaken);
    if (p->infd >= 0) {
	watchfd(p->infd);
	if (iobfhasdata(p->inf) && !FD_ISSET(p->infd, &poolreadyfds)) {
	   FD_SET(p->infd, &poolreadyfds);
	   poolnready++;
	}
    }
}
