initmsgs(void)
{
	int	i;
	jnmsg = gprompt(530);
	thrmsg = gprompt(532);
	eofmsg = gprompt(533);
	eopmsg = gprompt(534);
	startmsg = gprompt(535);
	endmsg = gprompt(536);
	haltmsg = gprompt(537);
	fsmsg = gprompt(538);
	bsmsg = gprompt(539);
	rjnmsg = gprompt(531);
	selogf = gprompt(6);
	lpost = strlen(startmsg);
	if  ((i = strlen(endmsg)) > lpost)
		lpost = i;
	if  ((i = strlen(haltmsg)) > lpost)
		lpost = i;
	Colstep = (COLS / (3 * 8)) * 8;
}
