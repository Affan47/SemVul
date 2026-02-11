is_in(char *needle, PMList *haystack)
{
	PMList *lp;

	for(lp = haystack; lp; lp = lp->next) {
		if(lp->data && !strcmp(lp->data, needle)) {
			return(1);
		}
	}
	return(0);
}
