listreverse(LIST *lp)
{
	LISTELEM *e1, *e2;
	VALUE tmp;
	long s;

	s = lp->l_count/2;
	e1 = lp->l_first;
	e2 = lp->l_last;
	lp->l_cache = NULL;
	while (s-- > 0) {
		tmp = e1->e_value;
		e1->e_value = e2->e_value;
		e2->e_value = tmp;
		e1 = e1->e_next;
		e2 = e2->e_prev;
	}
}
