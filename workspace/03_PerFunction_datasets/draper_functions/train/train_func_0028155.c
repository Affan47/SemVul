mahjongg_show_scores (Mahjongg* self, HistoryEntry* selected_entry, gboolean show_quit) {
	gint result = 0;
	ScoreDialog* dialog = NULL;
	History* _tmp0_ = NULL;
	HistoryEntry* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	ScoreDialog* _tmp3_ = NULL;
	GtkApplicationWindow* _tmp4_ = NULL;
	gint _result_ = 0;
	gint _tmp5_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->history;
	_tmp1_ = selected_entry;
	_tmp2_ = show_quit;
	_tmp3_ = score_dialog_new (_tmp0_, _tmp1_, _tmp2_);
	g_object_ref_sink (_tmp3_);
	dialog = _tmp3_;
	gtk_window_set_modal ((GtkWindow*) dialog, TRUE);
	_tmp4_ = self->priv->window;
	gtk_window_set_transient_for ((GtkWindow*) dialog, (GtkWindow*) _tmp4_);
	_tmp5_ = gtk_dialog_run ((GtkDialog*) dialog);
	_result_ = _tmp5_;
	gtk_widget_destroy ((GtkWidget*) dialog);
	result = _result_;
	_g_object_unref0 (dialog);
	return result;
}
