type() const {
    switch (rep()->xevent_.type) {
    case MotionNotify:
    case EnterNotify:
    case LeaveNotify:
	return motion;
    case ButtonPress:
	return down;
    case ButtonRelease:
	return up;
    case KeyPress:
	return key;
    case SelectionNotify:
	return selection_notify;
    default:
	return other_event;
    }
}
