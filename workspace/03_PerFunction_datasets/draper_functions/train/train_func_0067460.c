operand(int t)
{
	Reinst *i;

	if(lastwasand)
		operator(CAT);
	i = newinst(t);

	if(t == CCLASS || t == NCCLASS)
		i->u1.cp = yyclassp;
	if(t == RUNE)
		i->u1.r = yyrune;

	pushand(i, i);
	lastwasand = TRUE;
}
