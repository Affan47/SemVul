cb_line_color_changed (GOSelector *selector,
		       StylePrefState *state)
{
	GOStyle *style = state->style;

	g_return_if_fail (style != NULL);

	style->line.color = go_color_selector_get_color (selector, &style->line.auto_color);
	set_style (state);
}
