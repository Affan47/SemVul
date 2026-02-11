_e2_mkdirdlg_toggled3_cb (GtkWidget *menu_item, E2_MkdirDialogRuntime *rt)
{
	printd (DEBUG, "mkdir dialog suggest dir toggle");
	rt->opt_suggest_dir = gtk_check_menu_item_get_active
		(GTK_CHECK_MENU_ITEM (menu_item));
	_e2_mkdirdlg_update_name_and_status (rt);
	gpointer p = g_object_get_data (G_OBJECT (rt->dialog), "e2-controller-blocked");
	if (!GPOINTER_TO_INT (p))
		e2_option_bool_set_direct (suggest_dir, rt->opt_suggest_dir);
}
