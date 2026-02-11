change_callers(Subr *caller, int pos, int length, int new_length)
{
    if (up_to_date())
	return;
    update();

    int right = pos + length;
    int delta = new_length - length;
    for (int i = 0; i < _callers.size(); i++) {
	Caller &c = _callers[i];
	if (c.subr != caller)
	    ;
	else if (pos <= c.pos && c.pos + c.len <= right) {


	    c.subr = 0;
	} else if (right <= c.pos) {

	    c.pos += delta;
	} else if (c.pos <= pos && right <= c.pos + c.len) {
	    c.len += delta;
	} else
	    c.subr = 0;
    }
}
