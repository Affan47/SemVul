tracker_view_get_selected_path (TrackerView* self) {
	GtkTreePath* result = NULL;
	TrackerViewDisplay _tmp0_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_display;
	switch (_tmp0_) {
		case TRACKER_VIEW_DISPLAY_CATEGORIES:
		case TRACKER_VIEW_DISPLAY_FILE_LIST:
		{
			GtkWidget* _tmp1_;
			GtkTreeView* _tmp2_;
			GtkTreeView* v;
			GtkTreeView* _tmp3_;
			GtkTreeSelection* _tmp4_ = NULL;
			GtkTreeSelection* _tmp5_;
			GtkTreeSelection* s;
			GtkTreeSelection* _tmp6_;
			GList* _tmp7_ = NULL;
			GList* selected;
			GList* _tmp8_;
			gconstpointer _tmp9_ = NULL;
			GtkTreePath* _tmp10_;
			_tmp1_ = self->priv->view;
			_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp1_, GTK_TYPE_TREE_VIEW, GtkTreeView));
			v = _tmp2_;
			_tmp3_ = v;
			_tmp4_ = gtk_tree_view_get_selection (_tmp3_);
			_tmp5_ = _g_object_ref0 (_tmp4_);
			s = _tmp5_;
			_tmp6_ = s;
			_tmp7_ = gtk_tree_selection_get_selected_rows (_tmp6_, NULL);
			selected = _tmp7_;
			_tmp8_ = selected;
			_tmp9_ = g_list_nth_data (_tmp8_, (guint) 0);
			_tmp10_ = _gtk_tree_path_copy0 ((GtkTreePath*) _tmp9_);
			result = _tmp10_;
			__g_list_free__gtk_tree_path_free0_0 (selected);
			_g_object_unref0 (s);
			_g_object_unref0 (v);
			return result;
		}
		case TRACKER_VIEW_DISPLAY_FILE_ICONS:
		{
			GtkWidget* _tmp11_;
			GtkIconView* _tmp12_;
			GtkIconView* v;
			GtkIconView* _tmp13_;
			GList* _tmp14_ = NULL;
			GList* selected;
			GList* _tmp15_;
			gconstpointer _tmp16_ = NULL;
			GtkTreePath* _tmp17_;
			_tmp11_ = self->priv->view;
			_tmp12_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp11_, GTK_TYPE_ICON_VIEW, GtkIconView));
			v = _tmp12_;
			_tmp13_ = v;
			_tmp14_ = gtk_icon_view_get_selected_items (_tmp13_);
			selected = _tmp14_;
			_tmp15_ = selected;
			_tmp16_ = g_list_nth_data (_tmp15_, (guint) 0);
			_tmp17_ = _gtk_tree_path_copy0 ((GtkTreePath*) _tmp16_);
			result = _tmp17_;
			__g_list_free__gtk_tree_path_free0_0 (selected);
			_g_object_unref0 (v);
			return result;
		}
		default:
		{
			break;
		}
	}
	result = NULL;
	return result;
}
