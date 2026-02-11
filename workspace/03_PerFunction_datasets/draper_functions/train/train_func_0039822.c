node__get(Int ch)
{
	keymacro_node_t *ptr;

	ptr = el_malloc(sizeof(*ptr));
	if (ptr == NULL)
		return NULL;
	ptr->ch = ch;
	ptr->type = XK_NOD;
	ptr->val.str = NULL;
	ptr->next = NULL;
	ptr->sibling = NULL;
	return ptr;
}
