candidate_panel_set_auxiliary_text (CandidatePanel* self, IBusText* text) {
	IBusText* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = text;
	if (_tmp0_ != NULL) {
		GtkLabel* _tmp1_ = NULL;
		IBusText* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		GtkLabel* _tmp4_ = NULL;
		_tmp1_ = self->priv->m_aux_label;
		_tmp2_ = text;
		_tmp3_ = ibus_text_get_text (_tmp2_);
		gtk_label_set_text (_tmp1_, _tmp3_);
		_tmp4_ = self->priv->m_aux_label;
		gtk_widget_show ((GtkWidget*) _tmp4_);
	} else {
		GtkLabel* _tmp5_ = NULL;
		GtkLabel* _tmp6_ = NULL;
		_tmp5_ = self->priv->m_aux_label;
		gtk_label_set_text (_tmp5_, "");
		_tmp6_ = self->priv->m_aux_label;
		gtk_widget_hide ((GtkWidget*) _tmp6_);
	}
	candidate_panel_update (self);
}
