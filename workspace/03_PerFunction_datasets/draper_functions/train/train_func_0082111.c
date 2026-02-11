menuscreen_switch_item(MenuItem *new_menuitem)
{
	MenuItem *old_menuitem = active_menuitem;

	debug(RPT_DEBUG, "%s(item=[%s]) from active_menuitem=[%s]", __FUNCTION__,
	      ((new_menuitem != NULL) ? new_menuitem->id : "(null)"),
	      ((old_menuitem != NULL) ? old_menuitem->id : "(null)"));


	active_menuitem = new_menuitem;


	if (!old_menuitem && !new_menuitem) {

	} else if (old_menuitem && !new_menuitem) {

		menuscreen->priority = PRI_HIDDEN;
	} else if (!old_menuitem && new_menuitem) {

		menuitem_reset(active_menuitem);
		menuitem_rebuild_screen(active_menuitem, menuscreen);

		menuscreen->priority = PRI_INPUT;
	} else {

		if (old_menuitem->parent != new_menuitem) {
			menuitem_reset(new_menuitem);
		}
		menuitem_rebuild_screen(active_menuitem, menuscreen);
	}

        if (old_menuitem && old_menuitem->event_func)
	       old_menuitem->event_func(old_menuitem, MENUEVENT_LEAVE);
        if (new_menuitem && new_menuitem->event_func)
	       new_menuitem->event_func(new_menuitem, MENUEVENT_ENTER);

	return;
}
