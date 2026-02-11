array_remove(a, i)
ARRAY	*a;
arrayind_t	i;
{
	register ARRAY_ELEMENT *ae;

	if (a == 0 || array_empty(a))
		return((ARRAY_ELEMENT *) NULL);
	for (ae = element_forw(a->head); ae != a->head; ae = element_forw(ae))
		if (element_index(ae) == i) {
			ae->next->prev = ae->prev;
			ae->prev->next = ae->next;
			a->num_elements--;
			if (i == array_max_index(a))
				a->max_index = element_index(ae->prev);
			INVALIDATE_LASTREF(a);
			return(ae);
		}
	return((ARRAY_ELEMENT *) NULL);
}
