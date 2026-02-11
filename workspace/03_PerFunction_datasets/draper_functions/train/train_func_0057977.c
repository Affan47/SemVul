form_virtualize(WINDOW *w)
{
    int c = wgetch(w);

    switch (c) {
    case CTRL('W'):
	return (MY_CTRL_W);
    case CTRL('N'):
	return (MY_CTRL_N);
    case CTRL('P'):
	return (MY_CTRL_P);
    case QUIT:
    case ESCAPE:
	return (MY_CTRL_Q);

    case KEY_BACKSPACE:
	return (REQ_DEL_PREV);
    case KEY_DC:
	return (REQ_DEL_CHAR);
    case KEY_LEFT:
	return (REQ_LEFT_CHAR);
    case KEY_RIGHT:
	return (REQ_RIGHT_CHAR);

    case KEY_DOWN:
    case KEY_NEXT:
	return (REQ_NEXT_FIELD);
    case KEY_UP:
    case KEY_PREVIOUS:
	return (REQ_PREV_FIELD);

    default:
	return (c);
    }
}
