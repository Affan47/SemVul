toolbar_context_menu (GtkToolbar *tb, WBCGtk *gtk, GdkEventButton *event_button)
{
	GtkWidget *box = gtk_widget_get_parent (GTK_WIDGET (tb));
	GtkWidget *zone = gtk_widget_get_parent (GTK_WIDGET (box));
	GtkWidget *menu = gtk_menu_new ();
	GtkWidget *item;
	gboolean detached;

	static struct {
		char const *text;
		GtkPositionType pos;
	} const pos_items[] = {
		{ N_("Display above sheets"), GTK_POS_TOP },
		{ N_("Display to the left of sheets"), GTK_POS_LEFT },
		{ N_("Display to the right of sheets"), GTK_POS_RIGHT }
	};

#ifdef HAVE_GTK_HANDLE_BOX_FLOAT_WINDOW
	detached = (GTK_IS_HANDLE_BOX (box) &&
		    GTK_HANDLE_BOX (box)->child_detached);
#else
	detached = FALSE;
#endif
	if (detached) {
#ifdef HAVE_GTK_HANDLE_BOX_FLOAT_WINDOW
		item = gtk_menu_item_new_with_label (_("Reattach to main window"));
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
		g_signal_connect (G_OBJECT (item), "activate",
				  G_CALLBACK (cb_tcm_reattach),
				  box);
#endif
	} else {
		size_t ui;
		GSList *group = NULL;

		for (ui = 0; ui < G_N_ELEMENTS (pos_items); ui++) {
			char const *text = _(pos_items[ui].text);
			GtkPositionType pos = pos_items[ui].pos;

			item = gtk_radio_menu_item_new_with_label (group, text);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (item));

			gtk_check_menu_item_set_active
				(GTK_CHECK_MENU_ITEM (item),
				 (zone == gtk->toolbar_zones[pos]));

			gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
			g_object_set_data (G_OBJECT (item), "toolbar", tb);
			g_object_set_data (G_OBJECT (item), "side", GINT_TO_POINTER (pos));
			g_signal_connect (G_OBJECT (item), "activate",
					  G_CALLBACK (cb_set_toolbar_position),
					  gtk);
		}
	}

	item = gtk_menu_item_new ();
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
	gtk_widget_set_sensitive (item, FALSE);

	item = gtk_menu_item_new_with_label (_("Hide"));
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
	g_signal_connect (G_OBJECT (item), "activate",
			  G_CALLBACK (cb_tcm_hide),
			  box);

	gtk_widget_show_all (menu);
	gnumeric_popup_menu (GTK_MENU (menu), event_button);
}
