internal_code_name(InputCode code)
{
	const struct KeyboardInfo *keyinfo;
	const struct JoystickInfo *joyinfo;

	assert( code < code_mac );

	switch (code_map[code].type)
	{
		case CODE_TYPE_KEYBOARD :
			keyinfo = internal_code_find_keyboard(code);
			if (keyinfo)
				return keyinfo->name;
			break;
		case CODE_TYPE_JOYSTICK :
			joyinfo = internal_code_find_joystick(code);
			if (joyinfo)
				return joyinfo->name;
			break;
	}
	return "n/a";
}
