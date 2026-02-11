boolready(void)
{
	numitems = 0;
	if (item1 != NULL)
		free(item1);
	setsize1 = SETINC;
	if ((item1 = malloc(SETINC * sizeof(POSTING))) == NULL) {
		invcannotalloc(SETINC);
		return(-1);
	}
	if (item2 != NULL)
		free(item2);
	setsize2 = SETINC;
	if ((item2 = malloc(SETINC * sizeof(POSTING))) == NULL) {
		invcannotalloc(SETINC);
		return(-1);
	}
	item = item1;
	enditem = item;
	return(0);
}
