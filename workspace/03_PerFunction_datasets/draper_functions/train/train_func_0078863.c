constraint_count_attr(Entry *e, AttributeDescription *ad)
{
	struct Attribute *a;

	if ((a = attr_find(e->e_attrs, ad)) != NULL)
		return a->a_numvals;
	return 0;
}
