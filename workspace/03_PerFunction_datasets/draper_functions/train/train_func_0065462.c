historySearchBreak(history_ *r, history_ *next, double *time)
{
	ReturnErrIf(r == NULL);

	if(r->flag & HISTORY_FLAG_BRKPOINT) {
		return LIST_SEARCH_MATCH;
	}

	if(next == NULL) {
		return LIST_SEARCH_NOTONLIST;
	}

	return LIST_SEARCH_NEXT;
}
