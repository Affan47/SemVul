on_mouse_move(const CL_InputEvent &key)
{
	if (!input_enabled) return;

	int x = key.mouse_pos.x;
	int y = key.mouse_pos.y;

	owner->sig_transform_coords()(x, y);

	CL_Component *over_component = owner->get_component_at(
			x - owner->get_position().left,
			y - owner->get_position().top);

	focus_component = comp_capture_mouse;
	if (!comp_capture_mouse) focus_component = over_component;


	if (!focus_component) return;


	x -= focus_component->get_screen_rect().left;
	y -= focus_component->get_screen_rect().top;


	do_mouse_enter_leave(x, y, over_component);

	if (focus_component == 0) return;

	CL_InputEvent new_key = key;
	new_key.mouse_pos.x = x;
	new_key.mouse_pos.y = y;
	focus_component->sig_mouse_move()(new_key);
}
