handle_status_rm_command(String *args, int offset)
{
    ValueUnion uval;
    long row = -1;
    int opt;
    ListEntry *node;

    startopt(CS(args), "r#");
    while ((opt = nextopt(NULL, &uval, NULL, &offset))) {
	switch (opt) {
	case 'r':  row = uval.ival; break;
        default:   return shareval(val_zero);
	}
    }

    node = find_statusfield_by_name(row, args->data + offset);
    if (!node) return shareval(val_zero);
    row = ((StatusField*)(node->datum))->row;
    if (variable_width_field[row] == node->datum)
	variable_width_field[row] = NULL;
    if (!node->prev && getspacer(node->next)) {
	unlist(node->next, statusfield_list[row]);
    } else if (!node->next && getspacer(node->prev)) {
	unlist(node->prev, statusfield_list[row]);
    } else if (getspacer(node->prev) && getspacer(node->next)) {

	if (getspacer(node->prev) < getspacer(node->next))
	    unlist(node->prev, statusfield_list[row]);
	else
	    unlist(node->next, statusfield_list[row]);
    }
    unlist(node, statusfield_list[row]);
    regen_status_fields(row);
    return shareval(val_one);
}
