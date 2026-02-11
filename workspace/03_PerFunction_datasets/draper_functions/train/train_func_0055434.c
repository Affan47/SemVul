call_stack_frame_new (vgcaller_t type, const char *name)
{
	GtkWidget *hbox, *omenu, *entry;
	GtkWidget *menu, *item;

	hbox = gtk_hbox_new (FALSE, 6);

	omenu = gtk_option_menu_new ();
	menu = gtk_menu_new ();

	item = gtk_menu_item_new_with_label (_("Function"));
	gtk_widget_show (item);
	gtk_menu_shell_append ((GtkMenuShell *) menu, item);
	g_object_set_data ((GObject *) item, "vgcaller_t", GINT_TO_POINTER (VG_CALLER_FUNCTION));

	item = gtk_menu_item_new_with_label (_("Shared Object"));
	gtk_widget_show (item);
	gtk_menu_shell_append ((GtkMenuShell *) menu, item);
	g_object_set_data ((GObject *) item, "vgcaller_t", GINT_TO_POINTER (VG_CALLER_OBJECT));

	gtk_widget_show (menu);
	gtk_option_menu_set_menu ((GtkOptionMenu *) omenu, menu);
	gtk_option_menu_set_history ((GtkOptionMenu *) omenu, (int) type);

	gtk_widget_show (omenu);
	gtk_box_pack_start (GTK_BOX (hbox), omenu, FALSE, FALSE, 0);

	entry = gtk_entry_new ();
	gtk_entry_set_text ((GtkEntry *) entry, name ? name : "");
	gtk_widget_show (entry);
	gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);

	g_object_set_data ((GObject *) hbox, "omenu", omenu);
	g_object_set_data ((GObject *) hbox, "entry", entry);

	return hbox;
}
