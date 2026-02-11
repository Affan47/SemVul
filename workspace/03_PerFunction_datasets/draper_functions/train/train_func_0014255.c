lbox_select_first_item( LBox *lbox )
{
	if (lbox->items == NULL)
		return NULL;
	lbox->cur_item = list_first(lbox->items);
	lbox->cell_offset = 0;
	lbox_apply(lbox);
	return lbox->cur_item;
}
