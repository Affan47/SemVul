swap_file_roles(CONF_S *a, CONF_S *b)
{
    PAT_S      *pat_a, *pat_b;
    PAT_LINE_S *patline;

    pat_a = a->d.r.pat;
    pat_b = b->d.r.pat;
    patline = pat_a->patline;

    patline->dirty = 1;


    if(pat_a->next == pat_b){
	pat_b->prev = pat_a->prev;
	if(pat_a->prev)
	  pat_a->prev->next = pat_b;

	pat_a->next = pat_b->next;
	if(pat_b->next)
	  pat_b->next->prev = pat_a;

	pat_b->next = pat_a;
	pat_a->prev = pat_b;
    }
    else{
	PAT_S *new_a_prev, *new_a_next;

	new_a_prev = pat_b->prev;
	new_a_next = pat_b->next;

	pat_b->prev = pat_a->prev;
	pat_b->next = pat_a->next;
	if(pat_b->prev)
	  pat_b->prev->next = pat_b;
	if(pat_b->next)
	  pat_b->next->prev = pat_b;

	pat_a->prev = new_a_prev;
	pat_a->next = new_a_next;
	if(pat_a->prev)
	  pat_a->prev->next = pat_a;
	if(pat_a->next)
	  pat_a->next->prev = pat_a;
    }


    if(patline->first == pat_a)
      patline->first = pat_b;
    if(patline->last == pat_b)
      patline->last = pat_a;


    b->prev = a->prev;
    if(a->prev)
      a->prev->next = b;

    a->next = b->next;
    if(b->next)
      b->next->prev = a;

    b->next = a;
    a->prev = b;
}
