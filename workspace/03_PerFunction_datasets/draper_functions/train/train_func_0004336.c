gw_notebook_page_switch ( GtkNotebook *notebook, GtkNotebookPage *page, gint page_num, GtkWindow *w)
{
	GtkCList *clist = NULL;
	gboolean result = FALSE;
	static gboolean first_load = TRUE;
	GtkCombo *cmb = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		switch ( page_num )
		{
			case 0:	clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_explorer_page ( w, g_list_length ( clist->selection));

				result = TRUE;
				break;

			case 1:	clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_search_page ( w, g_list_length ( clist->selection));

				result = TRUE;
				break;

			case 2: gw_status_bar_set_catalog_managment_page ( w);


				if ( first_load)
				{
					first_load = FALSE;
					if ( (cmb = gw_notebook_managment_get_combo_box_device ( w)) != NULL)
					{
						gtk_widget_grab_focus ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))));
						gw_notebook_managment_select_device ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))), w);
					}
				}

				result = TRUE;
				break;

			default:return FALSE;
				break;
		}
	}

	return result;
}
