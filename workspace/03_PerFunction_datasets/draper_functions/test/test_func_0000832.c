on_mouse_move(const CL_InputEvent &key)
{
	if (pressed_by != PRESSED_BY_MOUSE)
		return;
	if(!button->is_mouse_captured())
		return;

	if(button->has_mouse_over())
		visually_down = !toggled;
	else
		visually_down = toggled;
}
