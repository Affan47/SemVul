e2_fs_complete_dir (GtkWidget *entry, guint keyval, guint pane)
{
	guint32 unikey = gdk_keyval_to_unicode (keyval);
	if (unikey > 0)
	{
		gchar keystring[8];
		gint bytes = g_unichar_to_utf8 (unikey, keystring);
		*(keystring+bytes) = '\0';
		gint type = e2_option_sel_get ("dir-line-completion");
		switch (type)
		{
			case 1:
				if (_e2_fs_complete_dir (entry, keystring, pane))
					return TRUE;
				break;
			case 2:
			{
				gint start, end, newpos, oldpos;
				if (gtk_editable_get_selection_bounds (GTK_EDITABLE (entry), &start, &end))
				{

					oldpos = start;
					gtk_editable_delete_text (GTK_EDITABLE (entry), start, end);
				}
				else
					oldpos = gtk_editable_get_position (GTK_EDITABLE (entry));

				if (_e2_fs_complete_dir (entry, keystring, pane))
				{
					newpos = gtk_editable_get_position (GTK_EDITABLE (entry));
					gtk_editable_select_region (GTK_EDITABLE (entry), oldpos+1, newpos);
					return TRUE;
				}
			}
				break;
			default:
				break;
		}
	}
	return FALSE;
}
