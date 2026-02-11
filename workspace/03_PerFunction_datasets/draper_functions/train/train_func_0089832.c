abraca_filter_view_on_header_remove (AbracaFilterView* self, GtkMenuItem* item) {
	GtkMenuItem* _tmp0_;
	GtkContainer* _tmp1_;
	GtkContainer* _tmp2_;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_;
	gchar* title;
	GList* _tmp5_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (item != NULL);
	_tmp0_ = item;
	_tmp1_ = gtk_widget_get_parent ((GtkWidget*) _tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = gtk_menu_get_title (GTK_MENU (_tmp2_));
	_tmp4_ = g_strdup (_tmp3_);
	title = _tmp4_;
	_tmp5_ = gtk_tree_view_get_columns ((GtkTreeView*) self);
	{
		GList* column_collection = NULL;
		GList* column_it = NULL;
		column_collection = _tmp5_;
		for (column_it = column_collection; column_it != NULL; column_it = column_it->next) {
			GtkTreeViewColumn* column = NULL;
			column = (GtkTreeViewColumn*) column_it->data;
			{
				GtkTreeViewColumn* _tmp6_;
				const gchar* _tmp7_;
				const gchar* _tmp8_;
				const gchar* _tmp9_;
				_tmp6_ = column;
				_tmp7_ = gtk_tree_view_column_get_title (_tmp6_);
				_tmp8_ = _tmp7_;
				_tmp9_ = title;
				if (g_strcmp0 (_tmp8_, _tmp9_) == 0) {
					GtkTreeViewColumn* _tmp10_;
					_tmp10_ = column;
					gtk_tree_view_remove_column ((GtkTreeView*) self, _tmp10_);
					break;
				}
			}
		}
		_g_list_free0 (column_collection);
	}
	_g_free0 (title);
}
