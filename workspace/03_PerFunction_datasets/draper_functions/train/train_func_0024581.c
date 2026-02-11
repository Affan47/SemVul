death_randarts(const char *title, int row)
{
	if (p_ptr->randarts)
		option_set(option_name(OPT_birth_keep_randarts),
			get_check("Keep randarts for next game? "));
	else
		msg("You are not playing with randarts!");
}
