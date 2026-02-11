get_escape_seq_abcd(int kbinput)
{
    switch (tolower(kbinput)) {
	case 'a':
	    return sc_seq_or(DO_UP_VOID, 0);;
	case 'b':
	    return sc_seq_or(DO_DOWN_VOID, 0);;
	case 'c':
	    return sc_seq_or(DO_RIGHT, 0);;
	case 'd':
	    return sc_seq_or(DO_LEFT, 0);;
	default:
	    return ERR;
    }
}
