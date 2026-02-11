menu_set_association(Menu *menu, void *assoc)
{


	debug(RPT_DEBUG, "%s(menu=[%s], assoc=[%s])", __FUNCTION__,
			((menu != NULL) ? menu->id : "(null)"),
			((assoc != NULL) ? "(data)" : "(null)"));


	if (menu == NULL)
		return;

	menu->data.menu.association = assoc;
}
