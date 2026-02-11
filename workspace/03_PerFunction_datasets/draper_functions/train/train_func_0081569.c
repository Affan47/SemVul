next_lstyle(char* s,int* ct) {
	char next[200];
	double temp;
	int is_alpha;
	int i,len;

	is_alpha=false;
	(*ct)++;
	doskip(tk[*ct],ct);
	strcpy(next,tk[*ct]);
	len = strlen(next);

	for(i=0 ; i < len ; i++) {
		is_alpha=isalpha((int)next[i]);
		if (is_alpha) i = len;
	}
	if (is_alpha) {

		polish_eval(next,&temp);
		sprintf(s,"%g",temp);
	} else {

		if (len < 9) {
			strcpy(s,next);
		} else {
			gprint("ERROR line style string too long %s\n",next);
		}
	}
}
