__lambda13_ (AbracaMainWindow* self, GtkAction* action) {
	AbracaConfig* _tmp0_;
	g_return_if_fail (action != NULL);
	_tmp0_ = self->priv->_config;
	abraca_config_show_sorting_dialog (_tmp0_, (GtkWindow*) self);
}
