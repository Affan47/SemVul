contacts_menu_button_real_button_release_event (GtkWidget* base, GdkEventButton* event) {
	ContactsMenuButton * self;
	gboolean result = FALSE;
	gboolean popup_in_progress_saved = FALSE;
	gboolean _tmp0_ = FALSE;
	GtkWidget* ewidget = NULL;
	GtkWidget* _tmp1_ = NULL;
	GtkWidget* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	GtkWidget* _tmp5_ = NULL;
	gboolean _tmp7_ = FALSE;
	gboolean _tmp9_ = FALSE;
	GtkWidget* _tmp11_ = NULL;
	self = (ContactsMenuButton*) base;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = self->priv->popup_in_progress;
	popup_in_progress_saved = _tmp0_;
	self->priv->popup_in_progress = FALSE;
	_tmp1_ = gtk_get_event_widget ((GdkEvent*) (event));
	_tmp2_ = _g_object_ref0 (_tmp1_);
	ewidget = _tmp2_;
	_tmp5_ = ewidget;
	if (_tmp5_ == G_TYPE_CHECK_INSTANCE_CAST (self, GTK_TYPE_WIDGET, GtkWidget)) {
		gboolean _tmp6_ = FALSE;
		_tmp6_ = popup_in_progress_saved;
		_tmp4_ = !_tmp6_;
	} else {
		_tmp4_ = FALSE;
	}
	_tmp7_ = _tmp4_;
	if (_tmp7_) {
		gboolean _tmp8_ = FALSE;
		_tmp8_ = gtk_toggle_button_get_active ((GtkToggleButton*) self);
		_tmp3_ = _tmp8_;
	} else {
		_tmp3_ = FALSE;
	}
	_tmp9_ = _tmp3_;
	if (_tmp9_) {
		GtkMenu* _tmp10_ = NULL;
		_tmp10_ = self->priv->menu;
		gtk_menu_popdown (_tmp10_);
		result = TRUE;
		_g_object_unref0 (ewidget);
		return result;
	}
	_tmp11_ = ewidget;
	if (_tmp11_ != G_TYPE_CHECK_INSTANCE_CAST (self, GTK_TYPE_WIDGET, GtkWidget)) {
		GtkMenu* _tmp12_ = NULL;
		_tmp12_ = self->priv->menu;
		gtk_menu_popdown (_tmp12_);
		result = TRUE;
		_g_object_unref0 (ewidget);
		return result;
	}
	result = FALSE;
	_g_object_unref0 (ewidget);
	return result;
}
