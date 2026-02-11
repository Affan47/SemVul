add_devices(CL_InputContext *ic)
{
	for (int k = 0; k < ic->get_keyboard_count(); k++)
	{
		impl->slots.connect(ic->get_keyboard(k).sig_key_down(), impl, &CL_InputBuffer_Generic::on_key_down);
		impl->slots.connect(ic->get_keyboard(k).sig_key_up(), impl, &CL_InputBuffer_Generic::on_key_up);
	}

	for (int m = 0; m < ic->get_mouse_count(); m++)
	{
		impl->slots.connect(ic->get_mouse(m).sig_key_down(), impl, &CL_InputBuffer_Generic::on_key_down);
		impl->slots.connect(ic->get_mouse(m).sig_key_up(), impl, &CL_InputBuffer_Generic::on_key_up);
	}

	for (int j = 0; j < ic->get_joystick_count(); j++)
	{
		impl->slots.connect(ic->get_joystick(j).sig_key_down(), impl, &CL_InputBuffer_Generic::on_key_down);
		impl->slots.connect(ic->get_joystick(j).sig_key_up(), impl, &CL_InputBuffer_Generic::on_key_up);
	}
}
