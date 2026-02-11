find_statusfield_by_template(StatusField *target,
    int full_comparison, const char *label)
{
    ListEntry *node;
    StatusField *f;
    int row;

    for (row = 0; row < status_height; row++) {
	if (target->row >= 0 && row != target->row) continue;
	for (node = statusfield_list[row]->head; node; node = node->next) {
	    f = (StatusField*)node->datum;
	    if (target->internal >= 0) {
		if (target->internal != f->internal) continue;
	    } else if (target->var) {
		if (!f->var || strcmp(target->name, f->var->val.name) != 0)
		    continue;
	    } else if (target->name) {
		if (!f->name || cstrcmp(target->name, f->name) != 0)
		    continue;
	    }
	    if (full_comparison) {
		if (target->width && target->width != f->width) continue;
		if (target->attrs && target->attrs != f->attrs) continue;
	    }
	    return node;
	}
    }
    if (label) {
	eprintf(
	    target->row<0 ? "%s: no such field" : "%s: no such field in row %d",
	    label, target->row);
    }
    return NULL;
}
