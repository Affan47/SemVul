_e2_confdlg_get_page (E2_OptionSet *set, E2_ConfigDialogRuntime *rt)
{
	GtkWidget *box;
	if ((box = (GtkWidget *) g_hash_table_lookup (rt->opthash, set->group)) == NULL)
	{
		gchar *frame = strrchr (set->group, ':');
		if (frame != NULL)
		{
			*frame = '\0';
			GtkWidget *frame_box;
			if ((frame_box = (GtkWidget *) g_hash_table_lookup (rt->opthash, set->group)) == NULL)
				frame_box = _e2_confdlg_get_page (set, rt);
			gchar *frame_title = e2_utils_str_stretch (frame + 1);
			GtkWidget *frame_widget = gtk_frame_new (frame_title);
			g_free (frame_title);
			GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
			gtk_container_add (GTK_CONTAINER (frame_widget), vbox);
			gtk_container_set_border_width (GTK_CONTAINER (vbox), E2_PADDING_SMALL);
			gtk_box_pack_start (GTK_BOX (frame_box), frame_widget, FALSE, FALSE, 0);
			box = vbox;
			*frame = ':';
		}
		else
		{
			gchar *child = strrchr (set->group, '.');
			if (child != NULL)
			{
				*child = '\0';
				box = _e2_confdlg_get_page (set, rt);
				if (page_last_name == NULL)

					page_last_name = g_strdup (set->group);
				GtkTreeIter *iter2;
				iter2 = g_object_get_data (G_OBJECT (box), "iter");
				if (iter2)
					box = _e2_confdlg_add_page (iter2, child + 1,
#ifdef NEWSCROLL
						set->type != E2_OPTION_TYPE_TREE,
#endif
						rt);
				*child = '.';
			}
			else
			{
				if (page_last_name == NULL)

					page_last_name = g_strdup (set->group);
				box = _e2_confdlg_add_page (NULL, set->group,
#ifdef NEWSCROLL
					set->type != E2_OPTION_TYPE_TREE,
#endif
					rt);
			}
		}
		g_hash_table_insert (rt->opthash, g_strdup(set->group), box);
	}
	return box;
}
