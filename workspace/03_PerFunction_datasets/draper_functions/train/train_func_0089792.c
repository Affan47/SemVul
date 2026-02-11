emacs(int c)
{
    el_status_t  s;
    el_keymap_t *kp;


    old_point = rl_point;

    if (rl_meta_chars && ISMETA(c)) {
	tty_push(UNMETA(c));
        return meta();
    }

    for (kp = Map; kp->Function; kp++) {
        if (kp->Key == c)
            break;
    }

    if (kp->Function) {
	s = kp->Function();
	if (s == CSdispatch)
	    s = insert_char(c);
    } else {
	s = insert_char(c);
    }

    if (!el_pushed) {

        Repeat = NO_ARG;
    }

    return s;
}
