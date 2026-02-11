checkintr(uh, val)
int uh, val;
{
	if (val >= 0 || errno != EINTR || validhost(uh, 0) < 0) return;
	safefclose(urlhostlist[uh].fp);
	urlhostlist[uh].fp = NULL;
	urlhostlist[uh].flags &= ~UFL_LOCKED;
	urlhostlist[uh].flags |= UFL_INTRED;
}
