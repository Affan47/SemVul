cumulative_changed_cb (GtkToggleButton *btn, GogHistogramPlot *model)
{
	if (gtk_toggle_button_get_active (btn) != model->cumulative) {
		model->cumulative = !model->cumulative;
		gog_object_request_update (GOG_OBJECT (model));
	}
}
