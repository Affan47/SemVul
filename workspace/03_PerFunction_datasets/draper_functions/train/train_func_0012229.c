main_window_get_views (MainWindow* self) {
	GeeList* result = NULL;
	GeeList* all_views = NULL;
	GeeLinkedList* _tmp0_ = NULL;
	DocumentsPanel* _tmp1_ = NULL;
	gint nb_documents = 0;
	DocumentsPanel* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = gee_linked_list_new (TYPE_DOCUMENT, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL);
	all_views = (GeeList*) _tmp0_;
	_tmp1_ = self->priv->_documents_panel;
	if (_tmp1_ == NULL) {
		result = all_views;
		return result;
	}
	_tmp2_ = self->priv->_documents_panel;
	_tmp3_ = gtk_notebook_get_n_pages ((GtkNotebook*) _tmp2_);
	nb_documents = _tmp3_;
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp4_ = FALSE;
			_tmp4_ = TRUE;
			while (TRUE) {
				gint _tmp6_ = 0;
				gint _tmp7_ = 0;
				DocumentTab* tab = NULL;
				DocumentsPanel* _tmp8_ = NULL;
				gint _tmp9_ = 0;
				GtkWidget* _tmp10_ = NULL;
				DocumentTab* _tmp11_ = NULL;
				GeeList* _tmp12_ = NULL;
				DocumentTab* _tmp13_ = NULL;
				DocumentView* _tmp14_ = NULL;
				DocumentView* _tmp15_ = NULL;
				if (!_tmp4_) {
					gint _tmp5_ = 0;
					_tmp5_ = i;
					i = _tmp5_ + 1;
				}
				_tmp4_ = FALSE;
				_tmp6_ = i;
				_tmp7_ = nb_documents;
				if (!(_tmp6_ < _tmp7_)) {
					break;
				}
				_tmp8_ = self->priv->_documents_panel;
				_tmp9_ = i;
				_tmp10_ = gtk_notebook_get_nth_page ((GtkNotebook*) _tmp8_, _tmp9_);
				_tmp11_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp10_, TYPE_DOCUMENT_TAB) ? ((DocumentTab*) _tmp10_) : NULL);
				tab = _tmp11_;
				_tmp12_ = all_views;
				_tmp13_ = tab;
				_tmp14_ = document_tab_get_view (_tmp13_);
				_tmp15_ = _tmp14_;
				gee_collection_add ((GeeCollection*) _tmp12_, _tmp15_);
				_g_object_unref0 (tab);
			}
		}
	}
	result = all_views;
	return result;
}
