gmpc_progress_enter_notify_event_callback (GmpcProgress* self, GtkWidget* scale, GdkEventCrossing* event) {
	gboolean result = FALSE;
	GdkEventCrossing _tmp0_;
	GdkEventType _tmp1_;
	GdkEventCrossing _tmp13_;
	GdkEventType _tmp14_;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (scale != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.type;
	if (_tmp1_ == GDK_ENTER_NOTIFY) {
		GtkWindow* _tmp2_;
		GtkWindow* _tmp4_;
		GtkWindow* _tmp5_;
		GtkLabel* _tmp6_;
		GtkLabel* _tmp7_;
		GtkWindow* _tmp8_;
		GtkLabel* _tmp9_;
		GtkWindow* _tmp10_;
		GtkWindow* _tmp11_;
		GtkWindow* _tmp12_;
		_tmp2_ = self->priv->tooltip;
		if (_tmp2_ != NULL) {
			GtkWindow* _tmp3_;
			_tmp3_ = self->priv->tooltip;
			gtk_object_destroy ((GtkObject*) _tmp3_);
		}
		_tmp4_ = (GtkWindow*) gtk_window_new (GTK_WINDOW_POPUP);
		_tmp5_ = g_object_ref_sink (_tmp4_);
		_g_object_unref0 (self->priv->tooltip);
		self->priv->tooltip = _tmp5_;
		_tmp6_ = (GtkLabel*) gtk_label_new ("test");
		_tmp7_ = g_object_ref_sink (_tmp6_);
		_g_object_unref0 (self->priv->tooltip_label);
		self->priv->tooltip_label = _tmp7_;
		_tmp8_ = self->priv->tooltip;
		_tmp9_ = self->priv->tooltip_label;
		gtk_container_add ((GtkContainer*) _tmp8_, (GtkWidget*) _tmp9_);
		_tmp10_ = self->priv->tooltip;
		gtk_container_set_border_width ((GtkContainer*) _tmp10_, (guint) 4);
		_tmp11_ = self->priv->tooltip;
		gtk_widget_set_app_paintable ((GtkWidget*) _tmp11_, TRUE);
		_tmp12_ = self->priv->tooltip;
		g_signal_connect_object ((GtkWidget*) _tmp12_, "expose-event", (GCallback) _gmpc_progress_tooltip_expose_event_callback_gtk_widget_expose_event, self, 0);
	}
	_tmp13_ = *event;
	_tmp14_ = _tmp13_.type;
	if (_tmp14_ == GDK_LEAVE_NOTIFY) {
		GtkWindow* _tmp15_;
		_tmp15_ = self->priv->tooltip;
		if (_tmp15_ != NULL) {
			GtkWindow* _tmp16_;
			_tmp16_ = self->priv->tooltip;
			gtk_object_destroy ((GtkObject*) _tmp16_);
			_g_object_unref0 (self->priv->tooltip);
			self->priv->tooltip = NULL;
		}
	}
	result = FALSE;
	return result;
}
