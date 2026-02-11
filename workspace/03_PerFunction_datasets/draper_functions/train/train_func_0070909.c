TwoBlank()
{
	register LinePtr	next = curline->l_next;

	return (next != NULL
		&& *(lcontents(next)) == '\0'
		&& next->l_next != NULL
		&& *(lcontents(next->l_next)) == '\0');
}
