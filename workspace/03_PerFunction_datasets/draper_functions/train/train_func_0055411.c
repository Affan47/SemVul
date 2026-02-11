emacs(unsigned int c)
{
    STATUS		s;
    KEYMAP		*kp;

    if (ISMETA(c) && rl_meta_chars)
    {
	el_Pushed = 1;
	el_PushBack = UNMETA(c);
	return meta();
    }
    for (kp = Map; kp->Function; kp++)
	if (kp->Key == c)
	    break;
    s = kp->Function ? (*kp->Function)() : insert_char((int)c);
    if (!el_Pushed)

	Repeat = NO_ARG;
    return s;
}
