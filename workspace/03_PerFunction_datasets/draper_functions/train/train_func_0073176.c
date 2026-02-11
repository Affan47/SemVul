display_feeling(bool obj_only)
{
	u16b obj_feeling = cave->feeling / 10;
	u16b mon_feeling = cave->feeling - (10 * obj_feeling);
	const char *join;


	if (OPT(birth_no_feelings)) return;


	if (!p_ptr->depth) {
		msg("Looks like a typical town.");
		return;
	}


	if (obj_only){
		msg("You feel that %s", obj_feeling_text[obj_feeling]);
		return;
	}


	if (cave->feeling_squares < FEELING1){
		msg("%s.", mon_feeling_text[mon_feeling]);
		return;
	}


	if (obj_feeling >= N_ELEMENTS(obj_feeling_text))
		obj_feeling = N_ELEMENTS(obj_feeling_text) - 1;

	if (mon_feeling >= N_ELEMENTS(mon_feeling_text))
		mon_feeling = N_ELEMENTS(mon_feeling_text) - 1;


	if ((mon_feeling <= 5 && obj_feeling > 6) ||
			(mon_feeling > 5 && obj_feeling <= 6))
		join = ", yet";
	else
		join = ", and";


	msg("%s%s %s", mon_feeling_text[mon_feeling], join,
		obj_feeling_text[obj_feeling]);
}
