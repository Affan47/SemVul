on_mouse_dblclk(const CL_InputEvent &key)
{
	if (!input_enabled) return;


	int mouse_x = (int) key.mouse_pos.x;
	int mouse_y = (int) key.mouse_pos.y;
	owner->sig_transform_coords()(mouse_x, mouse_y);

	CL_InputEvent transformed_key = key;
	transformed_key.mouse_pos.x = mouse_x;
	transformed_key.mouse_pos.y = mouse_y;


	focus_component = find_focus_component(transformed_key);
	if (!focus_component)
		return;


	if (focus_component->is_focusable())
		set_focus(focus_component);


	if (focus_component->is_enabled() == false || focus_component->is_visible() == false)
		return;


	transformed_key.mouse_pos.x -= focus_component->get_screen_rect().left;
	transformed_key.mouse_pos.y -= focus_component->get_screen_rect().top;


	focus_component->sig_input_down()(transformed_key);
	if (focus_component == 0) return;

	transformed_key.repeat_count = 2;


	focus_component->sig_mouse_dblclk()(transformed_key);
}
