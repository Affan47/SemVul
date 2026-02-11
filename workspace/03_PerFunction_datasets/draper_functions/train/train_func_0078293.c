list_merge(PMList *one, PMList *two)
{
	PMList *lp, *ptr;

	if(two == NULL) {
		return one;
	}

	ptr = one;
	if(ptr == NULL) {
		ptr = list_new();
	}

	for(lp = two; lp; lp = lp->next) {
		if(lp->data) {
			ptr = list_add(ptr, lp->data);
			lp->data = NULL;
		}
	}

	return(ptr);
}
