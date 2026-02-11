paddle_trigger(double dcycs)
{

	g_paddle_trig_dcycs = dcycs;


	paddle_fixup_joystick_type();

	switch(g_joystick_type) {
	case 0:
		paddle_trigger_keypad(dcycs);
		break;
	case 1:
		paddle_trigger_mouse(dcycs);
		break;
	default:
		joystick_update(dcycs);
	}
}
