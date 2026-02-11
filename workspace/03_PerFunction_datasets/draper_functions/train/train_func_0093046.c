checklistSetError( GtkWidget *psCheckList, const gchar *pnError ) {
	struct sCheckListDetails *psDetails;

	g_return_if_fail( psCheckList );

	psDetails = g_object_get_data( G_OBJECT( psCheckList ), "details" );
	g_assert( psDetails );

	if ( psDetails -> psBar != NULL ) {
		gtk_progress_bar_set_fraction( GTK_PROGRESS_BAR( psDetails -> psBar ), 1.0 );
		gtk_progress_bar_set_text( GTK_PROGRESS_BAR( psDetails -> psBar ), pnError );
	}
}
