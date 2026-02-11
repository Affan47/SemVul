add_lnum(linenum, pos)
	LINENUM linenum;
	POSITION pos;
{
	register struct linenum_info *p;
	register struct linenum_info *new;
	register struct linenum_info *nextp;
	register struct linenum_info *prevp;
	register POSITION mingap;


	for (p = anchor.next;  p != &anchor && p->pos < pos;  p = p->next)
		if (p->line == linenum)

			return;
	nextp = p;
	prevp = p->prev;

	if (freelist != NULL)
	{


		new = freelist;
		freelist = freelist->next;
	} else
	{


		new = spare;
		spare = NULL;
	}


	new->next = nextp;
	new->prev = prevp;
	new->pos = pos;
	new->line = linenum;

	nextp->prev = new;
	prevp->next = new;


	calcgap(new);
	calcgap(nextp);
	calcgap(prevp);

	if (spare == NULL)
	{


		mingap = anchor.next->gap;
		for (p = anchor.next;  p->next != &anchor;  p = p->next)
		{
			if (p->gap <= mingap)
			{
				spare = p;
				mingap = p->gap;
			}
		}
		spare->next->prev = spare->prev;
		spare->prev->next = spare->next;
	}
}
