joy_get_caps (int max)
{
	SDL_Joystick *joy;
	int j;

	for (j=0; j < JOY_NUM_AXES; j++)
		joystick.axis_valid[j] = 0;

	for (j=JOYSTICKID1; j<JOYSTICKID1+max; j++) {
		joy = SDL_JoystickOpen (j);
		if (joy)
		{
			nprintf (("JOYSTICK", "Joystick #%d: %s\n", j - JOYSTICKID1 + 1, SDL_JoystickName(j)));
			if (j == Cur_joystick) {
				for (int i = 0; i < SDL_JoystickNumAxes(joy); i++)
				{
					joystick.axis_valid[i] = 1;
				}
			}
			SDL_JoystickClose (joy);
		}
	}
}
