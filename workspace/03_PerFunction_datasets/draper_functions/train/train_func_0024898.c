gmpc_paned_size_group_add_paned (GmpcPanedSizeGroup* self, GtkPaned* paned) {
	GtkPaned* _tmp0_;
	GtkPaned* _tmp1_;
	GtkPaned* _tmp2_;
	gint _tmp3_;
	GtkPaned* _tmp4_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (paned != NULL);
	_tmp0_ = paned;
	g_signal_connect_object ((GObject*) _tmp0_, "notify::position", (GCallback) _gmpc_paned_size_group_child_position_changed_g_object_notify, self, 0);
	_tmp1_ = paned;
	g_signal_connect_object ((GtkWidget*) _tmp1_, "destroy-event", (GCallback) _gmpc_paned_size_group_child_destroy_event_gtk_widget_destroy_event, self, 0);
	self->priv->block_changed_callback = TRUE;
	_tmp2_ = paned;
	_tmp3_ = self->priv->position;
	gtk_paned_set_position (_tmp2_, _tmp3_);
	self->priv->block_changed_callback = FALSE;
	_tmp4_ = paned;
	self->priv->list = g_list_append (self->priv->list, _tmp4_);
}
