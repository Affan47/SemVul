addCase(case_info * last, char *guard, int gline,
			  char *action, int line, int *cnt)
{
    case_info *item;

    if (!guard && !action) {
	error(ERROR_WARNING,
	      "Case with neither guard nor action, line %d - ignored",
	      kwLine);
	return last;
    }

    *cnt = (*cnt) + 1;
    item = newof(0, case_info, 1, 0);
    item->guard = guard;
    item->action = action;
    item->next = 0;
    if (guard)
	item->gstart = gline;
    if (action)
	item->astart = line;

    if (last)
	last->next = item;

    return item;
}
