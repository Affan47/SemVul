gsb_autofunc_int_set_value ( GtkWidget *entry,
				  gint value,
				  gint number_for_func )
{
	gchar* tmpstr;


    if ( g_object_get_data (G_OBJECT (entry), "changed") > 0 )
	g_signal_handler_block ( G_OBJECT(entry),
				 (gulong) g_object_get_data (G_OBJECT (entry),
							     "changed"));
    if ( g_object_get_data (G_OBJECT (entry), "changed-hook") > 0 )
	g_signal_handler_block ( G_OBJECT(entry),
				 (gulong) g_object_get_data (G_OBJECT (entry),
							     "changed-hook"));


    tmpstr = utils_str_itoa (value);
    gtk_entry_set_text ( GTK_ENTRY(entry), tmpstr);
    g_free ( tmpstr );

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
