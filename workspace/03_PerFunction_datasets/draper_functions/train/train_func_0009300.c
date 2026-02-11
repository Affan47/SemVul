find_focus_component(const CL_InputEvent &key)
{
	CL_Component *focus_component = comp_focus;

	if (comp_capture_mouse)
	{
		focus_component = comp_capture_mouse;
	}
	else if (key.device.get_type() == CL_InputDevice::mouse)
	{
	focus_component = owner->get_component_at(
			(int)(key.mouse_pos.x - owner->get_position().left),
			(int)(key.mouse_pos.y - owner->get_position().top));
	}


	if (get_modal_component())
	{
		if (focus_component == get_modal_component() ||
			get_modal_component()->has_child(focus_component))
		{
		}
		else
		{
			focus_component = get_modal_component();
		}
	}

	return focus_component;
}
