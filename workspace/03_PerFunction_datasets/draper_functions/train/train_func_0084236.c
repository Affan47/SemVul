gen_one_contour(
    edge_struct *p_edges,
    double z_level,
    TBOOLEAN *contr_isclosed,
    int *num_active)
{
    edge_struct *pe_temp;

    if (! *contr_isclosed) {

	pe_temp = p_edges;
	while (pe_temp) {
	    if (pe_temp->is_active && (pe_temp->position == BOUNDARY))
		break;
	    pe_temp = pe_temp->next;
	}
	if (!pe_temp)
	    *contr_isclosed = TRUE;
	else {
	    return trace_contour(pe_temp, z_level, num_active, *contr_isclosed);
	}
    }
    if (*contr_isclosed) {

	pe_temp = p_edges;
	while (pe_temp) {
	    if (pe_temp->is_active && (pe_temp->position != BOUNDARY))
		break;
	    pe_temp = pe_temp->next;
	}
	if (!pe_temp) {
	    *num_active = 0;
	    fprintf(stderr, "gen_one_contour: no contour found\n");
	    return NULL;
	} else {
	    *contr_isclosed = TRUE;
	    return trace_contour(pe_temp, z_level, num_active, *contr_isclosed);
	}
    }
    return NULL;
}
