cs_build_menu (GOCharmapSel *cs)
{
        GtkWidget *item;
	GtkMenu *menu;
	LGroupInfo const *lgroup = lgroups;
	gint lg_cnt = 0;

        menu = GTK_MENU (gtk_menu_new ());

	while (lgroup->group_name) {
		CharsetInfo const *charset_trans;
		GtkMenu *submenu;
		gint cnt = 0;

		item = gtk_menu_item_new_with_label (_(lgroup->group_name));

		submenu = GTK_MENU (gtk_menu_new ());
		charset_trans = charset_trans_array;

		while (charset_trans->lgroup != LG_LAST) {
			GtkWidget *subitem;
			if (charset_trans->lgroup == lgroup->lgroup) {
				const char *name = (cs->test == GO_CHARMAP_SEL_TO_UTF8)
					? charset_trans->to_utf8_iconv_name
					: charset_trans->from_utf8_iconv_name;
				if (name) {
					subitem = gtk_check_menu_item_new_with_label
						(_(charset_trans->charset_title));
					gtk_widget_show (subitem);
					gtk_menu_shell_append ( GTK_MENU_SHELL (submenu), subitem );
					if (charset_trans->imp == CI_MAJOR)
						cs_emphasize_label (GTK_LABEL (gtk_bin_get_child (GTK_BIN (subitem))));
					g_object_set_data (G_OBJECT (subitem), CHARMAP_NAME_KEY,
							   (gpointer)name);
					cnt++;
				} else if (0) {
					g_print ("Unsupported: %s\n", charset_trans->aliases);
				}
			}
			charset_trans++;
		}
		if (cnt > 0) {
			gtk_menu_item_set_submenu ( GTK_MENU_ITEM (item), GTK_WIDGET (submenu) );
			gtk_widget_show (item);
			gtk_menu_shell_append ( GTK_MENU_SHELL (menu), item );
			lg_cnt++;
		} else {
			g_object_unref (item);
		}
                lgroup++;
        }
	item = gtk_separator_menu_item_new ();
	gtk_widget_show (item);
	gtk_menu_shell_append ( GTK_MENU_SHELL (menu), item );
	lg_cnt++;

	{
		char *locale_encoding_menu_title = g_strconcat (_("Locale: "),
							      get_locale_encoding_name (cs),
							      NULL);
		item = gtk_check_menu_item_new_with_label (locale_encoding_menu_title);
		g_free (locale_encoding_menu_title);
		gtk_widget_show (item);
		gtk_menu_shell_append ( GTK_MENU_SHELL (menu), item );
		lg_cnt++;
		cs_emphasize_label (GTK_LABEL (gtk_bin_get_child (GTK_BIN (item))));
	}

	go_option_menu_set_menu (cs->encodings, GTK_WIDGET (menu));
	cs->encodings_menu = menu;
	set_menu_to_default (cs, lg_cnt);
}
