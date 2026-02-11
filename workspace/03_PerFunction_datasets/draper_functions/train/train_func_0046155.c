single_tile_selection(int type)
{
	struct selected_element *s;
	if (list_empty(&selected_elements))
		return NULL;
	if (selected_elements.next->next != &selected_elements)
		return NULL;

	s = list_entry(selected_elements.next, struct selected_element, node);
	if (s->type != type)
		return NULL;

	return s->data;
}
