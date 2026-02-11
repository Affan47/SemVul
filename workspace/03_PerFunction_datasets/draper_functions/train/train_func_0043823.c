gmpc_tools_database_update_tracker_start_updating (GmpcToolsDatabaseUpdateTracker* self) {
	GtkImage* _tmp0_;
	GtkImage* _tmp1_;
	GtkImage* _tmp2_;
	GtkImage* _tmp3_;
	GtkImage* _tmp4_;
	const gchar* _tmp5_ = NULL;
	GtkImage* _tmp6_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->image;
	if (_tmp0_ != NULL) {
		return;
	}
	_tmp1_ = (GtkImage*) gtk_image_new_from_icon_name ("gtk-refresh", GTK_ICON_SIZE_MENU);
	_tmp2_ = g_object_ref_sink (_tmp1_);
	_g_object_unref0 (self->priv->image);
	self->priv->image = _tmp2_;
	_tmp3_ = self->priv->image;
	gtk_widget_show ((GtkWidget*) _tmp3_);
	_tmp4_ = self->priv->image;
	_tmp5_ = _ ("MPD is rescanning the database");
	gtk_widget_set_tooltip_text ((GtkWidget*) _tmp4_, _tmp5_);
	_tmp6_ = self->priv->image;
	main_window_add_status_icon ((GtkWidget*) _tmp6_);
}
