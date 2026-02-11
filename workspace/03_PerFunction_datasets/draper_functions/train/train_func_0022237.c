freecatalog(VOID_A)
{
	if (!catbuf) ;
#ifdef	USEMMAP
	else if (catbuf == (u_char *)MAP_FAILED) ;
	else if (catsize) VOID_C munmap(catbuf, catsize);
#endif
	else Xfree(catbuf);
	Xfree(catindex);

	catbuf = NULL;
	catsize = (ALLOC_T)0;
	catofs = (off_t)0;
	catindex = NULL;
	catmax = 0;
}
