tokenmode(int flag)
{
	int	oldflag;

	oldflag = TM_DEFAULT;
	if (newlines)
		oldflag |= TM_NEWLINES;
	if (allsyms)
		oldflag |= TM_ALLSYMS;
	newlines = FALSE;
	allsyms = FALSE;
	if (flag & TM_NEWLINES)
		newlines = TRUE;
	if (flag & TM_ALLSYMS)
		allsyms = TRUE;
	setprompt(newlines ? conf->prompt1 : conf->prompt2);
	return oldflag;
}
