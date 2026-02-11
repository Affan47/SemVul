gw_properties_box_get_disk_name ( GtkWidget *w)
{
	GtkWidget *entry = NULL;
	gchar *disk_name = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_PROPERTIES_BOX_DISK_NAME_ENTRY);

		if ( entry != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), disk_name);
		}
	}

	return disk_name;
}
