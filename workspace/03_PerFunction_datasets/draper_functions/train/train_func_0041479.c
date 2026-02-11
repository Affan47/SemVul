widget_lvledit_toolbar_scroll_right()
{
	struct widget_lvledit_categoryselect *cs = get_current_object_type();
	int i;

	for (i = 0; cs->indices[i] != -1; i++) ;

	cs->toolbar_first_block += 8;
	if (cs->toolbar_first_block >= i - 1)
		cs->toolbar_first_block -= 8;

	if (cs->selected_tile_nb < cs->toolbar_first_block)
		cs->selected_tile_nb = cs->toolbar_first_block;
}
