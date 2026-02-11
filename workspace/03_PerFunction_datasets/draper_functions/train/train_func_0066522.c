bin_changed_cb (GtkSpinButton *btn, struct color_map_edit_state *state)
{
	unsigned i;
	state->bin = gtk_spin_button_get_value (btn);
	for (i = 0; i < state->map->size && state->bin > state->map->limits[i]; i++);
	if (i < state->map->size) {
		gtk_widget_set_sensitive (go_gtk_builder_get_widget (state->gui, "erase"),
		                           i > 0 && state->bin == state->map->limits[i]);
		go_color_selector_set_color (GO_SELECTOR (state->color_selector),
		                             gog_axis_color_map_get_color (state->map, i));
	} else {
		gtk_widget_set_sensitive (go_gtk_builder_get_widget (state->gui, "erase"),
		                          FALSE);
		go_color_selector_set_color (GO_SELECTOR (state->color_selector),
		                             state->map->colors[state->map->size - 1]);
	}
}
