liqloc(loc)
int	loc;
{
	if (cond[loc]&LIQUID)
		return(liq2(cond[loc]&WATOIL));
	else
		return(liq2(1));
}
