code_pressed_not_memorized(InputCode code)
{
	int pressed;

	profiler_mark(PROFILER_INPUT);

	pressed = internal_code_pressed(code);

	if (pressed)
	{
		if (code_map[code].memory != 0)
			pressed = 0;
	} else
		code_map[code].memory = 0;

	profiler_mark(PROFILER_END);

	return pressed;
}
