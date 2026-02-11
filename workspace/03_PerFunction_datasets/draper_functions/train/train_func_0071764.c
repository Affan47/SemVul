process_sink_orphan(node *i)
{
	node *j;
	arc *a0, *a0_min = NULL, *a;
	nodeptr *np;
	int d, d_min = INFINITE_D;


	for (a0=i->first; a0; a0=a0->next)
	if (a0->r_cap)
	{
		j = a0 -> head;
		if (j->is_sink && (a=j->parent))
		{

			d = 0;
			while ( 1 )
			{
				if (j->TS == TIME)
				{
					d += j -> DIST;
					break;
				}
				a = j -> parent;
				d ++;
				if (a==TERMINAL)
				{
					j -> TS = TIME;
					j -> DIST = 1;
					break;
				}
				if (a==ORPHAN) { d = INFINITE_D; break; }
				j = a -> head;
			}
			if (d<INFINITE_D)
			{
				if (d<d_min)
				{
					a0_min = a0;
					d_min = d;
				}

				for (j=a0->head; j->TS!=TIME; j=j->parent->head)
				{
					j -> TS = TIME;
					j -> DIST = d --;
				}
			}
		}
	}

	if (i->parent = a0_min)
	{
		i -> TS = TIME;
		i -> DIST = d_min + 1;
	}
	else
	{

		i -> TS = 0;


		for (a0=i->first; a0; a0=a0->next)
		{
			j = a0 -> head;
			if (j->is_sink && (a=j->parent))
			{
				if (a0->r_cap) set_active(j);
				if (a!=TERMINAL && a!=ORPHAN && a->head==i)
				{

					j -> parent = ORPHAN;
					np = nodeptr_block -> New();
					np -> ptr = j;
					if (orphan_last) orphan_last -> next = np;
					else             orphan_first        = np;
					orphan_last = np;
					np -> next = NULL;
				}
			}
		}
	}
}
