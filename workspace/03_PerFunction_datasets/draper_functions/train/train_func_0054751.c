addw(Word *w, char *s)
{
	Word *lw;

	for(lw = w; w = w->next; lw = w){
		if(strcmp(s, w->s) == 0)
			return;
	}
	lw->next = newword(s);
}
