calcgap(p)
	register struct linenum_info *p;
{


	if (p == &anchor || p->next == &anchor)
		return;
	p->gap = p->next->pos - p->prev->pos;
}
