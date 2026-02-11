spell_entry_add_suggestions_menu (ESpellEntry *entry,
                                  GtkMenu *menu,
                                  const gchar *word)
{
	GtkWidget *icon, *mi;

	g_return_if_fail (menu != NULL);
	g_return_if_fail (word != NULL);


	mi = gtk_separator_menu_item_new ();
	gtk_widget_show (mi);
	gtk_menu_shell_prepend (GTK_MENU_SHELL (menu), mi);


	icon = gtk_image_new_from_stock (GTK_STOCK_SPELL_CHECK, GTK_ICON_SIZE_MENU);
	mi = gtk_image_menu_item_new_with_label (_("Spelling Suggestions"));
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (mi), icon);

	gtk_menu_item_set_submenu (GTK_MENU_ITEM (mi), build_spelling_menu (entry, word));

	gtk_widget_show_all (mi);
	gtk_menu_shell_prepend (GTK_MENU_SHELL (menu), mi);
}
