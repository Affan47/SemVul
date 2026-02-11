gmpc_browsers_metadata_metadata_box_clear (GmpcBrowsersMetadata* self) {
	GtkEventBox* _tmp0_;
	GList* _tmp1_ = NULL;
	GList* list;
	GList* _tmp2_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->metadata_box;
	_tmp1_ = gtk_container_get_children ((GtkContainer*) _tmp0_);
	list = _tmp1_;
	_tmp2_ = list;
	{
		GList* child_collection = NULL;
		GList* child_it = NULL;
		child_collection = _tmp2_;
		for (child_it = child_collection; child_it != NULL; child_it = child_it->next) {
			GtkWidget* _tmp3_;
			GtkWidget* child = NULL;
			_tmp3_ = _g_object_ref0 ((GtkWidget*) child_it->data);
			child = _tmp3_;
			{
				GtkWidget* _tmp4_;
				_tmp4_ = child;
				gtk_object_destroy ((GtkObject*) _tmp4_);
				_g_object_unref0 (child);
			}
		}
	}
	_g_list_free0 (list);
}
