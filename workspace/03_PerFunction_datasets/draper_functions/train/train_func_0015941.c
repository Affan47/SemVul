replaceinlist(struct stringlist **haystack, char *needle, size_t len)
{
    struct stringlist **f = lfindinlist(haystack, needle, len);
    struct stringlist *n;
    if (!f) prependtolist(haystack, needle);
    else {
	n = (*f)->next;
    	free(*f);
    	*f = (struct stringlist *)critmalloc(sizeof(struct stringlist) +
			strlen(needle), "Allocating space in stringlist");
	strcpy((*f)->string, needle);
	(*f)->next = n;
    }
}
