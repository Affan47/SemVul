node__delete(EditLine *el, key_node_t **inptr, const Char *str)
{
	key_node_t *ptr;
	key_node_t *prev_ptr = NULL;

	ptr = *inptr;

	if (ptr->ch != *str) {
		key_node_t *xm;

		for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
			if (xm->sibling->ch == *str)
				break;
		if (xm->sibling == NULL)
			return (0);
		prev_ptr = xm;
		ptr = xm->sibling;
	}
	if (*++str == '\0') {

		if (prev_ptr == NULL)
			*inptr = ptr->sibling;
		else
			prev_ptr->sibling = ptr->sibling;
		ptr->sibling = NULL;
		node__put(el, ptr);
		return (1);
	} else if (ptr->next != NULL &&
	    node__delete(el, &ptr->next, str) == 1) {
		if (ptr->next != NULL)
			return (0);
		if (prev_ptr == NULL)
			*inptr = ptr->sibling;
		else
			prev_ptr->sibling = ptr->sibling;
		ptr->sibling = NULL;
		node__put(el, ptr);
		return (1);
	} else {
		return (0);
	}
}
