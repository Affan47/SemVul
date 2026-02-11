klotski_show_scores (Klotski* self, HistoryEntry* selected_entry, gboolean show_quit) {
	gint result = 0;
	History* _tmp0_;
	HistoryEntry* _tmp1_;
	gboolean _tmp2_;
	GtkActionGroup* _tmp3_;
	ScoreDialog* _tmp4_;
	ScoreDialog* dialog;
	GtkWindow* _tmp5_;
	gint _tmp6_ = 0;
	gint _result_;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->history;
	_tmp1_ = selected_entry;
	_tmp2_ = show_quit;
	_tmp3_ = self->priv->gaction_group;
	_tmp4_ = score_dialog_new (_tmp0_, _tmp1_, _tmp2_, _tmp3_);
	g_object_ref_sink (_tmp4_);
	dialog = _tmp4_;
	gtk_window_set_modal ((GtkWindow*) dialog, TRUE);
	_tmp5_ = self->priv->window;
	gtk_window_set_transient_for ((GtkWindow*) dialog, _tmp5_);
	_tmp6_ = gtk_dialog_run ((GtkDialog*) dialog);
	_result_ = _tmp6_;
	gtk_widget_destroy ((GtkWidget*) dialog);
	result = _result_;
	_g_object_unref0 (dialog);
	return result;
}
