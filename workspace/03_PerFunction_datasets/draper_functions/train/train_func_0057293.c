regtry(regexp *prog, char *string)
{
	register int i;
	register char **sp;
	register char **ep;

	reginput = string;
	regstartp = prog->startp;
	regendp = prog->endp;

	sp = prog->startp;
	ep = prog->endp;
	for (i = NSUBEXP; i > 0; i--) {
		*sp++ = NULL;
		*ep++ = NULL;
	}
	if (regmatch(prog->program + 1)) {
		prog->startp[0] = string;
		prog->endp[0] = reginput;
		return(1);
	} else
		return(0);
}
