dbstring_free(DBSTRING ** dbstrp)
{
	DBSTRING *curr, *next;


	if (!dbstrp)
		return;

	curr = *dbstrp;
	*dbstrp = NULL;
	for (; curr; ) {
		next = curr->strnext;
		free(curr->strtext);
		free(curr);
		curr = next;
	}
}
