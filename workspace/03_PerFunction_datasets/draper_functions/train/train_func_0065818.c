Atari800_SetMachineType(int type)
{
	Atari800_machine_type = type;
	if (Atari800_machine_type != Atari800_MACHINE_XLXE) {
		Atari800_builtin_basic = FALSE;
		Atari800_keyboard_leds = FALSE;
		Atari800_f_keys = FALSE;
		Atari800_jumper = FALSE;
		Atari800_builtin_game = FALSE;
		Atari800_keyboard_detached = FALSE;
	}
}
