tigetstr(NCURSES_CONST char *str)
{
    unsigned i;

    T((T_CALLED("tigetstr(%s)"), str));

    if (cur_term != 0) {
	TERMTYPE *tp = &(cur_term->type);
	for_each_string(i, tp) {
	    const char *capname = ExtStrname(tp, i, strnames);
	    if (!strcmp(str, capname)) {

		returnPtr(tp->Strings[i]);
	    }
	}
    }

    returnPtr(CANCELLED_STRING);
}
