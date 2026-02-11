pval(io *f, word *a)
{
	if(a){
		while(a->next && a->next->word){
			pwrd(f, a->word);
			pchr(f, ' ');
			a = a->next;
		}
		pwrd(f, a->word);
	}
}
