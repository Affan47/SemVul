ui_text_select_lines(GtkWidget *w, unsigned long startline, unsigned long endline)
{
#if GTK2
#ifdef HAVE_GTK_TEXT_BUFFER_SELECT_RANGE
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(w));
    GtkTextIter start, end;

    if (startline > 1)
    	startline--;

    gtk_text_buffer_get_iter_at_line(buffer, &start, startline);
    gtk_text_buffer_get_iter_at_line(buffer, &end, endline);


    gtk_text_buffer_select_range(buffer, &start, &end);
#else


    GtkTextViewClass *klass = GTK_TEXT_VIEW_GET_CLASS(w);
    GtkTextView *tview = GTK_TEXT_VIEW(w);

    (*klass->move_cursor)(tview, GTK_MOVEMENT_BUFFER_ENDS, -1, FALSE);

    if (startline > 1)
	(*klass->move_cursor)(tview, GTK_MOVEMENT_DISPLAY_LINES,
    	    	    	      (gint)startline-1, FALSE);

    if (endline == startline)
	(*klass->move_cursor)(tview, GTK_MOVEMENT_DISPLAY_LINE_ENDS,
    	    	    	      1, TRUE);
    else
	(*klass->move_cursor)(tview, GTK_MOVEMENT_DISPLAY_LINES,
    	    	    	      (gint)(endline - startline + 1),
			      TRUE);
#endif
#else
    ui_text_data *td = (ui_text_data *)gtk_object_get_data(GTK_OBJECT(w),
    	    	    	    	    	    	    	   ui_text_data_key);
    int endoff;

    assert(td->offsets_by_line->len > 0);

    if (startline < 1)
    	startline = 1;
    if (endline < 1)
    	endline = startline;
    if (startline > td->offsets_by_line->len)
    	startline = td->offsets_by_line->len;
    if (endline > td->offsets_by_line->len)
    	endline = td->offsets_by_line->len;
    if (startline > endline)
    	return;

    assert(startline >= 1);
    assert(startline <= td->offsets_by_line->len);
    assert(endline >= 1);
    assert(endline <= td->offsets_by_line->len);


    if (endline == td->offsets_by_line->len)
	endoff = -1;
    else
	endoff = g_array_index(td->offsets_by_line, unsigned int, endline)-1;

    gtk_editable_select_region(GTK_EDITABLE(w),
    	    g_array_index(td->offsets_by_line, unsigned int, startline-1),
    	    endoff);
#endif
}
