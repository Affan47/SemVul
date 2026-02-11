gsb_autofunc_entry_set_value ( GtkWidget *entry,
				    const gchar *value,
				    gint number_for_func )
{

    if ( g_object_get_data (G_OBJECT (entry), "changed") > 0 )
	g_signal_handler_block ( G_OBJECT(entry),
				 (gulong) g_object_get_data (G_OBJECT (entry),
							     "changed"));
    if ( g_object_get_data (G_OBJECT (entry), "changed-hook") > 0 )
	g_signal_handler_block ( G_OBJECT(entry),
				 (gulong) g_object_get_data (G_OBJECT (entry),
							     "changed-hook"));


    if (value)
	gtk_entry_set_text ( GTK_ENTRY ( entry ), value );
    else
	gtk_entry_set_text ( GTK_ENTRY ( entry ), "" );

    g_object_set_data ( G_OBJECT (entry),
			"number_for_func", GINT_TO_POINTER (number_for_func));


    if ( g_object_get_data (G_OBJECT (entry), "changed") > 0 )
	g_signal_handler_unblock ( G_OBJECT(entry),
				   (gulong) g_object_get_data (G_OBJECT (entry),
							       "changed"));
    if ( g_object_get_data (G_OBJECT (entry), "changed-hook") > 0 )
	g_signal_handler_unblock ( G_OBJECT(entry),
				   (gulong) g_object_get_data (G_OBJECT (entry),
							       "changed-hook"));
}
