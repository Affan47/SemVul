mkposcl (state)
     int     state;
{
	int     eps;

	if (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		return state;
	}

	else {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		return link_machines (state, eps);
	}
}
