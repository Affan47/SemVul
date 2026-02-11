hasverb(int act,int *verbs)
{
    int link,word,*verb;


    link = getafield(act,A_VERBS);


    while (link != NIL) {
	verb = verbs;
	word = getword(link+L_DATA);
	while (*verb != NIL && word != NIL) {
	    if (*verb != getword(word+L_DATA))
		break;
	    verb++;
	    word = getword(word+L_NEXT);
	}
	if (*verb == NIL && word == NIL)
	    return (TRUE);
	link = getword(link+L_NEXT);
    }
    return (FALSE);
}
