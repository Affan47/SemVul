breakpoint_destroy(b)
struct breakpoint *b;
{
	if (b->file) Tcl_DecrRefCount(b->file);
	if (b->pat) Tcl_DecrRefCount(b->pat);
	if (b->cmd) Tcl_DecrRefCount(b->cmd);
	if (b->expr) Tcl_DecrRefCount(b->expr);


	if ((b->previous == 0) && (b->next == 0)) {
		break_base = 0;
	} else if (b->previous == 0) {
		break_base = b->next;
		b->next->previous = 0;
	} else if (b->next == 0) {
		b->previous->next = 0;
	} else {
		b->previous->next = b->next;
		b->next->previous = b->previous;
	}

	ckfree((char *)b);
}
