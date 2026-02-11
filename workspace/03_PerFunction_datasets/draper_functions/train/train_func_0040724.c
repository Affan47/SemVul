nautilus_query_editor_add_row (NautilusQueryEditor *editor,
			       NautilusQueryEditorRowType type)
{
	GtkWidget *hbox, *button, *image, *combo;
	GtkToolItem *item;
	NautilusQueryEditorRow *row;
	int i;

	row = g_new0 (NautilusQueryEditorRow, 1);
	row->editor = editor;
	row->type = type;


	row->toolbar = gtk_toolbar_new ();
	gtk_box_pack_start (GTK_BOX (editor), row->toolbar, TRUE, TRUE, 0);

	item = gtk_tool_item_new ();
	gtk_tool_item_set_expand (item, TRUE);
	gtk_toolbar_insert (GTK_TOOLBAR (row->toolbar), item, -1);

	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_container_add (GTK_CONTAINER (item), hbox);
	row->hbox = hbox;


	combo = gtk_combo_box_text_new ();
	row->combo = combo;
	for (i = 0; i < NAUTILUS_QUERY_EDITOR_ROW_LAST; i++) {
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), gettext (row_type[i].name));
	}
	gtk_box_pack_start (GTK_BOX (hbox), combo, FALSE, FALSE, 0);

	gtk_combo_box_set_active (GTK_COMBO_BOX (combo), row->type);

	editor->details->rows = g_list_append (editor->details->rows, row);

	g_signal_connect (combo, "changed",
			  G_CALLBACK (row_type_combo_changed_cb), row);

	create_type_widgets (row);


	button = gtk_button_new ();
	gtk_style_context_add_class (gtk_widget_get_style_context (button),
				     GTK_STYLE_CLASS_RAISED);
	gtk_widget_set_tooltip_text (button,
				     _("Remove this criterion from the search"));
	gtk_box_pack_end (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	image = gtk_image_new_from_icon_name ("window-close-symbolic",
					      GTK_ICON_SIZE_MENU);
	gtk_container_add (GTK_CONTAINER (button), image);

	g_signal_connect (button, "clicked",
			  G_CALLBACK (remove_row_cb), row);


	gtk_widget_show_all (row->toolbar);

	return row;
}
