select_clist (GtkWidget *clist,
	 	   gint row,
		   gint column __unused,
		   GdkEventButton * bevent) {

    gchar *tmp_cookie[COOKIE_COLUMNS];
    gint i;


    initialise_cookie(tmp_cookie);

    for (i = 0; i < COOKIE_COLUMNS; i++) {
	switch (gtk_clist_get_cell_type (GTK_CLIST (clist), row, i)) {
	case GTK_CELL_TEXT:
	    gtk_clist_get_text(GTK_CLIST (clist), row, i, &tmp_cookie[i]);
	    break;

	default:
	    break;
	}
    }


    copy_cookie(tmp_cookie, glbl_selected_cookie);


    glbl_clist_selected_row = row;


    if (bevent != NULL && bevent->button == 3) {
	gtk_menu_popup (GTK_MENU(glbl_cookie_menu_item_holder),
			NULL, NULL, NULL, NULL,
			bevent->button, bevent->time);
    }

}
