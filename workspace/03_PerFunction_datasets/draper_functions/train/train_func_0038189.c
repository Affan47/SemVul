menu_add_item (GtkWidget *menu, menu_entry *me, char *target)
{
	GtkWidget *item = NULL;
	char *path = me->path + me->root_offset;

	if (path[0] != 0)
		menu = menu_find_path (menu, path);
	if (menu)
	{
		item = menu_quick_item (me->cmd, me->label, menu, me->markup ? XCMENU_MARKUP|XCMENU_MNEMONIC : XCMENU_MNEMONIC, target, me->icon);
		menu_reorder (GTK_MENU (menu), item, me->pos);
	}
	return item;
}
