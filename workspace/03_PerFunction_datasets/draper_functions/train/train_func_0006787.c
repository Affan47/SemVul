beginPrint( GtkPrintOperation *psOperation, GtkPrintContext *psContext, gpointer pUserData ) {
	PrintData *psData = ( PrintData * ) pUserData;
	GtkTreeModel *psModel;
	GtkTreeIter sIter;
	gboolean bValid;
	PangoFontDescription *psDesc = pango_font_description_from_string( FONT );

	psData -> nNumLines = 0;

	psModel = gtk_tree_view_get_model( psData -> psView );
	bValid = gtk_tree_model_get_iter_first( psModel, &sIter );
	while ( bValid ) {
		bValid = gtk_tree_model_iter_next( psModel, &sIter );
		psData -> nNumLines++;
	}

	psData -> psLayout = gtk_print_context_create_pango_layout( psContext );
	pango_layout_set_wrap( psData -> psLayout, PANGO_WRAP_WORD_CHAR );
	pango_layout_set_spacing( psData -> psLayout, 0 );
	pango_layout_set_attributes( psData -> psLayout, NULL );
	pango_layout_set_font_description( psData -> psLayout, psDesc );

	psData -> nNumPages = get_page_count( psContext, psData );
	psData -> fFontWidth = get_font_width( psContext, psDesc ) + 1;
	if ( psData -> fFontWidth == 0 ) {
		psData -> fFontWidth = psData -> fCharWidth;
	}

	Debug( KERN_DEBUG, "nNumPages: %d\n", psData -> nNumPages);

	psData -> nLogoPos = 4;
	psData -> nDateTimePos = psData -> nLogoPos + psData -> fFontWidth * 4;
	psData -> nNamePos = psData -> nDateTimePos + psData -> fFontWidth * 12;
	psData -> nNumberPos = psData -> nNamePos + psData -> fFontWidth * 19;
	psData -> nLocalNamePos = psData -> nNumberPos + psData -> fFontWidth * 14;
	psData -> nLocalNumberPos = psData -> nLocalNamePos + psData -> fFontWidth * 11;
	psData -> nDurationPos = psData -> nLocalNumberPos + psData -> fFontWidth * 14;

	if ( psData -> nNumPages >= 0 ) {
		gtk_print_operation_set_n_pages( psOperation, psData -> nNumPages );
	}

	pango_font_description_free( psDesc );
}
