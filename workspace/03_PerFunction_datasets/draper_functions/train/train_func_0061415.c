trace(char *s, Arc *a)
{
	fprint(2, "\t%s", s);
	while(a){
		fprint(2, " <-(%s:%d)- %s", a->r->file, a->r->line,
			a->n? a->n->name:"");
		if(a->n){
			for(a = a->n->prereqs; a; a = a->next)
				if(*a->r->recipe) break;
		} else
			a = 0;
	}
	fprint(2, "\n");
}
