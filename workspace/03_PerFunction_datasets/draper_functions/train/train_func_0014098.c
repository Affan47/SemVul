__lambda45_ (ClocksStopwatchMainPanel* self, GtkWidget* w) {
	ClocksStopwatchMainPanelState _tmp0_ = 0;
	g_return_if_fail (w != NULL);
	_tmp0_ = self->priv->state;
	if (_tmp0_ == CLOCKS_STOPWATCH_MAIN_PANEL_STATE_RUNNING) {
		clocks_stopwatch_main_panel_remove_tick (self);
	}
}
