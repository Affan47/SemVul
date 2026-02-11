list_element(list l, int num)
{
	element e = LIST_HEAD(l);
	int i = 0;


	for (i = 0; i < num; i++)
		if (e)
			ELEMENT_NEXT(e);
	if (e)
		return ELEMENT_DATA(e);
	return NULL;
}
