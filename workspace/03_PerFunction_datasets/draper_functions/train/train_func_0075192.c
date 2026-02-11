join_lines(struct COOR *p, struct COOR *q)
{
    p->row = row;
    p->col = col - 1;

    switch (data_type) {
    case CELL_TYPE:
	p->val = ((CELL *) middle)[col];
	break;
    case FCELL_TYPE:
	p->dval = ((FCELL *) middle)[col];
	break;
    case DCELL_TYPE:
	p->dval = ((DCELL *) middle)[col];
	break;
    default:
	break;
    }

    G_debug(3, "join_lines: p: row:%d, col:%d; q: row:%d, col:%d",
	    p->row, p->col, q->row, q->col);

    if (p->fptr != NULL) {
	G_warning(_("join_lines: p front pointer not NULL!"));

    }

    p->fptr = q->bptr;
    if (q->fptr != NULL) {
	G_warning(_("join_lines: q front pointer not NULL!"));

    }

    if (q->bptr->fptr == q)
	q->bptr->fptr = p;
    else
	q->bptr->bptr = p;

    G_free(q);
    write_line(p);

    return 0;
}
