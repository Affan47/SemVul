socksendoob(s, buf, size)
int s;
CONST VOID_P buf;
ALLOC_T size;
{
	int n;

# ifdef	NOSENDFLAGS
	n = seterrno(EIO);
# else
	n = send(s, buf, size, MSG_OOB);
	if (n >= 0 && (ALLOC_T)n < size) n = seterrno(EIO);
# endif

	return(n);
}
