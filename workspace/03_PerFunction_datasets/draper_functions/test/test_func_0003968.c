e_get_text(earray *a, int index)
{
	if (a && index>=0 && index<a->len)
		return a->data[index].str->str;

	return NULL;
}
