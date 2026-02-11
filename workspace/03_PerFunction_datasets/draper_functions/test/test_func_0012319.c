tgetflag(NCURSES_CONST char *id)
{
    unsigned i;

    T((T_CALLED("tgetflag(%s)"), id));
    if (cur_term != 0) {
	TERMTYPE *tp = &(cur_term->type);
	for_each_boolean(i, tp) {
	    const char *capname = ExtBoolname(tp, i, boolcodes);
	    if (!strncmp(id, capname, 2)) {

		returnCode(tp->Booleans[i]);
	    }
	}
    }
    returnCode(0);
}
