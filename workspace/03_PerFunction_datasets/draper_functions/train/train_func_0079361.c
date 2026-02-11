make_sick(xtime, cause, talk, type)
long xtime;
const char *cause;
boolean talk;
int type;
{
	long old = Sick;

	if (xtime > 0L) {
	    if (Sick_resistance) return;
	    if (!old) {

		You_feel("deathly sick.");
	    } else {

		if (talk) You_feel("%s worse.",
			      xtime <= Sick/2L ? "much" : "even");
	    }
	    set_itimeout(&Sick, xtime);
	    u.usick_type |= type;
	    flags.botl = TRUE;
	} else if (old && (type & u.usick_type)) {

	    u.usick_type &= ~type;
	    if (u.usick_type) {
		if (talk) You_feel("somewhat better.");
		set_itimeout(&Sick, Sick * 2);
	    } else {
		if (talk) pline("What a relief!");
		Sick = 0L;
	    }
	    flags.botl = TRUE;
	}

	if (Sick) {
	    exercise(A_CON, FALSE);
	    if (cause) {
		(void) strncpy(u.usick_cause, cause, sizeof(u.usick_cause));
		u.usick_cause[sizeof(u.usick_cause)-1] = 0;
		}
	    else
		u.usick_cause[0] = 0;
	} else
	    u.usick_cause[0] = 0;
}
