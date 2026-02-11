region_inside(const region *loc, const ui_event *key)
{
	if ((loc->col > key->mouse.x) || (loc->col + loc->width <= key->mouse.x))
		return FALSE;

	if ((loc->row > key->mouse.y) || (loc->row + loc->page_rows <= key->mouse.y))
		return FALSE;

	return TRUE;
}
