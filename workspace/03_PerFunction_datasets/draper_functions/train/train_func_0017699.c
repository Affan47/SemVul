sat_pref_help_create ()
{
     GtkWidget *vbox;
     GtkWidget *table;
     GtkWidget *label;
     guint      i;
     gint       idx;

     vbox = gtk_vbox_new (FALSE, 10);
     gtk_container_set_border_width (GTK_CONTAINER (vbox), 20);


     label = gtk_label_new (NULL);
     gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
     gtk_label_set_markup (GTK_LABEL (label),
                     _("<b>Html Browser:</b>"));
     gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, TRUE, 0);


     table = gtk_table_new (2, 2, TRUE);
     gtk_table_set_col_spacings (GTK_TABLE (table), 10);
     gtk_table_set_row_spacings (GTK_TABLE (table), 10);
     gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, TRUE, 0);


     label = gtk_label_new (_("Browser type:"));
     gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
     gtk_table_attach (GTK_TABLE (table), label, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0, 0);

     combo = gtk_combo_box_new_text ();
     for (i = 0; i < BROWSER_TYPE_NUM; i++)
          gtk_combo_box_append_text (GTK_COMBO_BOX (combo), sat_help[i].type);
     gtk_table_attach (GTK_TABLE (table), combo, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
     g_signal_connect (combo, "changed", G_CALLBACK (browser_changed_cb), NULL);


     label = gtk_label_new (_("Command string:"));
     gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
     gtk_table_attach (GTK_TABLE (table), label, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 0, 0);

     entry = gtk_entry_new ();
     gtk_entry_set_max_length (GTK_ENTRY (entry), 100);
     gtk_table_attach (GTK_TABLE (table), entry, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 0, 0);


     idx = sat_cfg_get_int (SAT_CFG_INT_WEB_BROWSER_TYPE);


     if ((idx < BROWSER_TYPE_NONE) || (idx >= BROWSER_TYPE_NUM)) {
          idx = BROWSER_TYPE_NONE;
     }

     gtk_combo_box_set_active (GTK_COMBO_BOX (combo), idx);
     if (idx == BROWSER_TYPE_OTHER)
          gtk_entry_set_text (GTK_ENTRY (entry),
                        sat_cfg_get_str (SAT_CFG_STR_WEB_BROWSER));


     gtk_widget_set_sensitive (vbox, FALSE);


     dirty = FALSE;

     return vbox;
}
