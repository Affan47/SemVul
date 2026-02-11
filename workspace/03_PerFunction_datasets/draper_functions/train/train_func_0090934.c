gc_board_config_combo_locales(GcomprisBoardConf *config, gchar *init)
{
  g_return_val_if_fail(config, NULL);
  GtkWidget *combobox;
  GtkWidget *hbox = gtk_hbox_new (FALSE, 8);
  GList *list, *strings;
  GtkWidget *label_combo;
  gint init_index = 0;

  strings = gc_locale_gets_list_name();


  strings = g_list_prepend( strings, g_strdup( gc_locale_get_name("") ) );

  if (init)
    {
      const gchar *init_name = gc_locale_get_name( init );
      init_index = g_list_position(strings,
				   g_list_find_custom(strings,
						      (gconstpointer) init_name,
						      (GCompareFunc) g_strcmp0));
    }

  if (init_index < 0)
    init_index=0;

  gtk_widget_show(hbox);

  gtk_box_pack_start (GTK_BOX(config->main_conf_box),
		      hbox,
		      FALSE,
		      FALSE,
		      0);


  label_combo = gtk_label_new ((gchar *)NULL);
  gtk_widget_show(label_combo);
  gtk_box_pack_start (GTK_BOX(hbox),
		      label_combo,
		      FALSE,
		      FALSE,
		      0);

  gtk_label_set_justify (GTK_LABEL(label_combo),
			 GTK_JUSTIFY_RIGHT);

  gtk_label_set_markup (GTK_LABEL(label_combo),
                        _("Select the language\n to use in the board"));

  combobox = GTK_WIDGET(gtk_combo_box_new_text());

  gtk_widget_show(combobox);

  gtk_box_pack_start (GTK_BOX(hbox),
		      combobox,
		      FALSE,
		      FALSE,
		      0);


  for (list = strings; list != NULL; list = list->next)
    gtk_combo_box_append_text (GTK_COMBO_BOX(combobox),
			       list->data);

  if (g_list_length(strings) > COMBOBOX_COL_MAX)
    gtk_combo_box_set_wrap_width    (GTK_COMBO_BOX(combobox),
  	     g_list_length(strings) / COMBOBOX_COL_MAX +1 );

  gtk_combo_box_set_active (GTK_COMBO_BOX(combobox),
			    init_index);
  _gc_boardconf_key *u = g_malloc0(sizeof(_gc_boardconf_key));
  u -> key = g_strdup("locale");
  u -> config = config;
  g_signal_connect(G_OBJECT(combobox),
		   "changed",
		   G_CALLBACK(gc_board_config_combo_locales_changed),
		   u);
  g_signal_connect(G_OBJECT(combobox),
  	"destroy",
	G_CALLBACK(_gc_destroy_boardconf_key),
	u);

  return GTK_COMBO_BOX(combobox);

}
