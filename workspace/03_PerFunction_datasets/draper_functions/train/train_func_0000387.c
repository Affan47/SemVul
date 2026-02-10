mark_beginning_as_normal (mach)
     register int mach;
{
	switch (state_type[mach]) {
	case STATE_NORMAL:

		return;

	case STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_NORMAL;

		if (transchar[mach] == SYM_EPSILON) {
			if (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans1[mach]);

			if (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans2[mach]);
		}
		break;

	default:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		break;
	}
}
