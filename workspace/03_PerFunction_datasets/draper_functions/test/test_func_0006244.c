reffunc(id)
char *id;
{	int i;

	if (idsearch(id)!=NIL)
		yyerror("conflict between function and variable");
	for (i=0; i<functop; i++)
		if (strcompare(id,function[i].name)==0)
			return(i);
	if (functop>=FUNCMAX)
		fatal("too many functions");
	function[functop].name=entername(id,0);
	function[functop].pos=(-1);
	return(functop++);
}
