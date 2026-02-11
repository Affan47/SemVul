partition_clist(GtkWidget *clist,
			    SORT_STYLE sort_style,
			    gint sort_column,
			    gint first_index,
			    gint *pivot_index,
			    gint last_index) {

    gchar *pivot_cookie[COOKIE_COLUMNS];
    gchar *sort_column_cell_contents;
    gchar *cell_contents;
    gchar *more_cell_contents;
    gint col;
    int (*compfunction)(const char*, const char*);


    gint too_big_index = first_index + 1;
    gint too_small_index = last_index;


    initialise_cookie(pivot_cookie);


    copy_clist_row_to_cookie(first_index, pivot_cookie);


    if (sort_style == STRING) {
	compfunction = strcmp;
    } else {
	compfunction = intcmp;
    }
    while (too_big_index <= too_small_index) {
	gtk_clist_get_text(GTK_CLIST (clist), too_big_index, sort_column,
			   &sort_column_cell_contents);


	while (too_big_index <= last_index && (*compfunction)(sort_column_cell_contents, pivot_cookie[sort_column]) <= 0) {
	    ++too_big_index;
	    gtk_clist_get_text(GTK_CLIST (clist), too_big_index, sort_column,
			       &sort_column_cell_contents);
	}
	gtk_clist_get_text(GTK_CLIST (clist), too_small_index, sort_column,
			   &sort_column_cell_contents);


	while ((*compfunction)(sort_column_cell_contents, pivot_cookie[sort_column]) > 0) {
	    --too_small_index;
	    gtk_clist_get_text(GTK_CLIST (clist), too_small_index, sort_column,
			       &sort_column_cell_contents);
	}
	if (too_big_index < too_small_index) {
	    swap_row_clist(clist, too_big_index, too_small_index);

	    gtk_clist_get_text(GTK_CLIST (clist), too_big_index, sort_column,
			       &cell_contents);
	    gtk_clist_get_text(GTK_CLIST (clist), too_small_index, sort_column,
			       &more_cell_contents);
	}
    }

    *pivot_index = too_small_index;


    if (first_index != *pivot_index) {
	for (col = 0; col < COOKIE_COLUMNS; col++) {
	    gtk_clist_get_text(GTK_CLIST (clist), *pivot_index, col,
			       &cell_contents);
	    gtk_clist_set_text(GTK_CLIST (clist), first_index, col,
			       cell_contents);
	}
    }

    for (col = 0; col < COOKIE_COLUMNS; col++) {
	gtk_clist_set_text(GTK_CLIST (clist), *pivot_index, col,
			   pivot_cookie[col]);
    }


    free_cookie(pivot_cookie);
}
