addrgather_page_finish( gint pageNum, gchar *pageLbl ) {
	GtkWidget *label;
	GtkWidget *vbox;
	GtkWidget *clistSWin;
	GtkWidget *clistCount;
	gchar *titles[ FIELDS_N_COLS ];
	gint i;
	titles[ FIELD_COL_HEADER ] = _("Header Name");
	titles[ FIELD_COL_COUNT  ] = _("Address Count");

	vbox = gtk_vbox_new(FALSE, 8);
	gtk_container_add( GTK_CONTAINER( addrgather_dlg.notebook ), vbox );
	gtk_container_set_border_width( GTK_CONTAINER (vbox), 8 );

	label = gtk_label_new( pageLbl );
	gtk_widget_show( label );
	gtk_notebook_set_tab_label(
		GTK_NOTEBOOK( addrgather_dlg.notebook ),
		gtk_notebook_get_nth_page( GTK_NOTEBOOK( addrgather_dlg.notebook ), pageNum ),
		label );


	clistSWin = gtk_scrolled_window_new( NULL, NULL );
	gtk_container_add( GTK_CONTAINER(vbox), clistSWin );
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(clistSWin),
				       GTK_POLICY_AUTOMATIC,
				       GTK_POLICY_AUTOMATIC);

	clistCount = gtk_cmclist_new_with_titles( FIELDS_N_COLS, titles );
	gtk_container_add( GTK_CONTAINER(clistSWin), clistCount );
	gtk_cmclist_set_selection_mode( GTK_CMCLIST(clistCount), GTK_SELECTION_BROWSE );
	gtk_cmclist_set_column_width(
			GTK_CMCLIST(clistCount), FIELD_COL_HEADER, FIELDS_COL_WIDTH_HEADER );
	gtk_cmclist_set_column_width(
			GTK_CMCLIST(clistCount), FIELD_COL_COUNT, FIELDS_COL_WIDTH_COUNT );

	for( i = 0; i < FIELDS_N_COLS; i++ )
		gtkut_widget_set_can_focus(GTK_CMCLIST(clistCount)->column[i].button, FALSE);

	addrgather_dlg.clistCount = clistCount;
}
