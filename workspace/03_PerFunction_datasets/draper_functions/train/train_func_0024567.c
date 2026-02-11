do_cmd_delay(const char *name, int row)
{
	char tmp[4] = "";
	int msec = op_ptr->delay_factor;

	strnfmt(tmp, sizeof(tmp), "%i", op_ptr->delay_factor);

	screen_save();


	prt("Command: Base Delay Factor", 20, 0);

	prt(format("Current base delay factor: %d msec",
			   op_ptr->delay_factor, msec), 22, 0);
	prt("New base delay factor (0-255): ", 21, 0);


	if (askfor_aux(tmp, sizeof(tmp), askfor_aux_numbers)) {
		u16b val = (u16b) strtoul(tmp, NULL, 0);
		op_ptr->delay_factor = MIN(val, 255);
	}

	screen_load();
}
