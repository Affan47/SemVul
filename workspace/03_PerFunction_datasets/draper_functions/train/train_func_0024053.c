gl_label_get_short_name (glLabel *label)
{
	gl_debug (DEBUG_LABEL, "");

	if ( label->priv->filename == NULL )
        {

		if ( label->priv->untitled_instance == 0 )
                {
			label->priv->untitled_instance = ++untitled;
		}

		return g_strdup_printf ( "%s %d", _("Untitled"),
					 label->priv->untitled_instance );

	}
        else
        {
		gchar *temp_name, *short_name;

		temp_name = g_path_get_basename ( label->priv->filename );
		short_name = gl_file_util_remove_extension (temp_name);
		g_free (temp_name);

		return short_name;
	}
}
