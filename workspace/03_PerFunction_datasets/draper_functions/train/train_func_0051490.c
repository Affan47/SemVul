go_color_selector_get_color (GOSelector *selector, gboolean *is_auto)
{
	GOColorSelectorState *state;
	int index;
	gboolean flag;

	g_return_val_if_fail (GO_IS_SELECTOR (selector), GO_COLOR_WHITE);

	index = go_selector_get_active (selector, &flag);
	state = go_selector_get_user_data (selector);
	if (is_auto != NULL)
		*is_auto = flag;


	if (flag)
		return state->default_color;

	return get_color (state->n_swatches, state->color_group, index);
}
