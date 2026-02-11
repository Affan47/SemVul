tokenize_html(char* t)
{
list_t * l = NULL,*tl=NULL;
unsigned int position=0;
regmatch_t p[1];
unsigned int len = strlen(t);

int bag = MODE_PLAIN;

do	{
	p[0].begin = -1;
	p[0].end = -1;
	regexec_my(&t[position],p,&bag);
	if(p[0].end != -1)
		{
		int start1,start2,stop1,stop2;

		start2 = position+p[0].begin;
		stop2= position+p[0].end;

		start1=position;
		stop1=position+p[0].begin;

		l=list_add_fast(l,&tl,new_token(start1,stop1,0));
		if(start2+1 < stop2-1)
			l=list_add_fast(l,&tl,
				new_token(start2+1,stop2-1,TOK_TAG));
		}
	position+=p[0].end;
	}
while(p[0].begin != -1 && position < len);

return l;
}
