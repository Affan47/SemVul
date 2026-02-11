insert(off, endp, which)
char	*off,
	*endp;
int which;
{
	register char	*pp = pstrtlst[which];
	register int	n;

	if (pp == NULL)
		complain("\\%d not defined", which);

	n  = pendlst[which] - pp;


	if (off + n >= endp)
		len_error(JMP_ERROR);

	while (--n >= 0)
		*off++ = *pp++;
	return off;
}
