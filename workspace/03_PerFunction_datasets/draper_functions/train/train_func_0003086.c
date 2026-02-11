list_switch(struct widget *w, int how)
{
	struct widget *jmp;
	if (how == NEXT_WIDGET) {
		if (w->current->next) {
			for (jmp = w->current->next; jmp; SWITCH(jmp))
				if (jmp->selectable && jmp->hidden == 0) {
					w->current = jmp;
					break;
				}
		} else if (w->wheel && w->current != w->kids)
			for (jmp = w->kids; jmp->next != w->current; SWITCH(jmp))
				if (jmp->selectable && jmp->hidden == 0) {
					w->current = jmp;
					break;
				}
	} else if (how == PREV_WIDGET) {
		if (w->current != w->kids) {
			struct widget *arg = w->current;
			for (; arg != w->kids; arg = jmp) {
				for (jmp = w->kids; jmp->next != arg; SWITCH(jmp));
				if (jmp->selectable && jmp->hidden == 0) {
					w->current = jmp;
					break;
				}
			}
		} else if (w->wheel)
			if (w->last->selectable && w->last->hidden == 0)
				w->current = w->last;
	}

}
