contacts_revealer_real_style_updated (GtkWidget* base) {
	ContactsRevealer * self;
	gboolean _tmp0_ = FALSE;
	self = (ContactsRevealer*) base;
	GTK_WIDGET_CLASS (contacts_revealer_parent_class)->style_updated ((GtkWidget*) G_TYPE_CHECK_INSTANCE_CAST (self, GTK_TYPE_BIN, GtkBin));
	_tmp0_ = gtk_widget_get_realized ((GtkWidget*) self);
	if (_tmp0_) {
		GtkStyleContext* context = NULL;
		GtkStyleContext* _tmp1_ = NULL;
		GtkStyleContext* _tmp2_ = NULL;
		GtkStyleContext* _tmp3_ = NULL;
		GdkWindow* _tmp4_ = NULL;
		GtkStyleContext* _tmp5_ = NULL;
		GdkWindow* _tmp6_ = NULL;
		_tmp1_ = gtk_widget_get_style_context ((GtkWidget*) self);
		_tmp2_ = _g_object_ref0 (_tmp1_);
		context = _tmp2_;
		_tmp3_ = context;
		_tmp4_ = self->priv->bin_window;
		gtk_style_context_set_background (_tmp3_, _tmp4_);
		_tmp5_ = context;
		_tmp6_ = self->priv->view_window;
		gtk_style_context_set_background (_tmp5_, _tmp6_);
		_g_object_unref0 (context);
	}
}
