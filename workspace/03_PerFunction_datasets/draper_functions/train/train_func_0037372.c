fixupins(P *p, long amnt, long nlines, H *hdr, int hdramnt)
{
	P *pp;

	if (nlines && !pisbol(p))
		scrins(p->b, p->line, nlines, 1);
	else
		scrins(p->b, p->line, nlines, 0);
	inserr(p->b->name, p->line, nlines, pisbol(p));

	for (pp = p->link.next; pp != p; pp = pp->link.next)
		if (pp->line == p->line && (pp->byte > p->byte || (pp->end && pp->byte == p->byte)))
			pp->valcol = 0;
	for (pp = p->link.next; pp != p; pp = pp->link.next)
		if (pp->byte == p->byte && !pp->end)
			if (pp->ptr)
				pset(pp, p);
			else
				poffline(pset(pp, p));
		else if (pp->byte > p->byte || (pp->end && pp->byte == p->byte)) {
			pp->byte += amnt;
			pp->line += nlines;
			if (pp->hdr == hdr)
				pp->ofst += hdramnt;
		}
	if (p->b->undo)
		undoins(p->b->undo, p, amnt);
	p->b->changed = 1;
}
