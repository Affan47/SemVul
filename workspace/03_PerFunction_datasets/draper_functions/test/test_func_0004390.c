floor_layers_button_right_click(struct widget_button *wb)
{
	int next_layer = current_floor_layer + 1;
	if (next_layer >= EditLevel()->floor_layers)
		next_layer = 0;
	action_change_floor_layer(EditLevel(), next_layer);
}
