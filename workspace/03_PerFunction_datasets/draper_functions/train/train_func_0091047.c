gtk_combofix_expose_entry ( GtkComboFix *combofix )
{
    if ( block_expose_event )
	    return FALSE;

    block_expose_event = 1;

    gtk_editable_select_region ( GTK_EDITABLE (combofix -> entry),
				 gtk_editable_get_position (GTK_EDITABLE ( combofix -> entry) ),
				 -1 );
    return FALSE;
}
