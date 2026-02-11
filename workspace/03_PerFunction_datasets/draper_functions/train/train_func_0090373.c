operator(int t)
{
	if(t==RBRA && --nbra<0)
		rcerror("unmatched right paren");
	if(t==LBRA){
		if(++cursubid >= NSUBEXP)
			rcerror ("too many subexpressions");
		nbra++;
		if(lastwasand)
			operator(CAT);
	} else
		evaluntil(t);
	if(t != RBRA)
		pushator(t);
	lastwasand = FALSE;
	if(t==STAR || t==QUEST || t==PLUS || t==RBRA)
		lastwasand = TRUE;
}
