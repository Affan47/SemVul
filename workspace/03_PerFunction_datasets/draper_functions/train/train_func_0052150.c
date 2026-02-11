gsb_report_update_report_list ( void )
{
    GSList *list_tmp;
    GtkTreeIter iter;


    if (!report_model_filter)
	return FALSE;

    gtk_list_store_clear (GTK_LIST_STORE (report_model));


    list_tmp = gsb_data_report_get_report_list ();

    while ( list_tmp )
    {
	gint report_number;

	report_number = gsb_data_report_get_report_number (list_tmp -> data);

	gtk_list_store_append ( GTK_LIST_STORE (report_model),
				&iter );

	gtk_list_store_set ( GTK_LIST_STORE (report_model),
			     &iter,
			     REPORT_COL_NAME, gsb_data_report_get_report_name (report_number),
			     REPORT_COL_NUMBER, report_number,
			     REPORT_COL_VIEW, TRUE,
			     -1 );
	list_tmp = list_tmp -> next;
    }
    return FALSE;
}
