create_set_filetype_menu(void)
{
	GSList *node;
	GtkWidget *filetype_menu = ui_lookup_widget(main_widgets.window, "set_filetype1_menu");

	create_sub_menu(filetype_menu, GEANY_FILETYPE_GROUP_COMPILED, _("_Programming Languages"));
	create_sub_menu(filetype_menu, GEANY_FILETYPE_GROUP_SCRIPT, _("_Scripting Languages"));
	create_sub_menu(filetype_menu, GEANY_FILETYPE_GROUP_MARKUP, _("_Markup Languages"));
	create_sub_menu(filetype_menu, GEANY_FILETYPE_GROUP_MISC, _("M_iscellaneous"));


	foreach_slist(node, filetypes_by_title)
	{
		GeanyFiletype *ft = node->data;

		if (ft->group != GEANY_FILETYPE_GROUP_NONE)
			create_radio_menu_item(group_menus[ft->group], ft);
		else
			create_radio_menu_item(filetype_menu, ft);
	}
}
