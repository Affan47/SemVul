gmpc_mpddata_treeview_save_column_setup (GmpcMpdDataTreeview * self)
{
#line 543 "gmpc-mpddata-treeview.c"
#define __GOB_FUNCTION__ "Gmpc:MpdData:Treeview::save_column_setup"
#line 243 "gmpc-mpddata-treeview.gob"
	g_return_if_fail (self != NULL);
#line 243 "gmpc-mpddata-treeview.gob"
	g_return_if_fail (GMPC_IS_MPDDATA_TREEVIEW (self));
#line 549 "gmpc-mpddata-treeview.c"
{
#line 246 "gmpc-mpddata-treeview.gob"

			int i=0;
			GList *iter,*cols = gtk_tree_view_get_columns(GTK_TREE_VIEW(self));
			gchar *conf_pos = NULL;
			gchar *conf_show = NULL;

			i = g_list_length(cols);

			if(i != NUM_COLS)
			{
				g_list_free(cols);
				return;
			}
			conf_pos = g_strdup_printf("%s-colpos", self->_priv->name);
			conf_show = g_strdup_printf("%s-colshow", self->_priv->name);

			i=0;
			for(iter = cols; iter; iter = g_list_next(iter))
			{
				GtkTreeViewColumn *column = iter->data;
				int id = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(column), "id"));
				cfg_set_single_value_as_int(config, conf_pos, col_names[id], i);
				cfg_set_single_value_as_int(config, conf_show, col_names[id], gtk_tree_view_column_get_visible(column));


				i++;
			}
			q_free(conf_pos);
			q_free(conf_show);

			g_list_free(cols);

			if(self->_priv->do_sort)
			{
				int sort_col;
				GtkSortType sort_order;
				gtk_tree_sortable_get_sort_column_id(GTK_TREE_SORTABLE(gtk_tree_view_get_model(GTK_TREE_VIEW(self))), &sort_col, &sort_order);
				cfg_set_single_value_as_int(config, self->_priv->name, "sort-column",sort_col);
				cfg_set_single_value_as_int(config, self->_priv->name, "sort-order", sort_order);
			}
		}}
