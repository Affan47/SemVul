swap_literal_roles(CONF_S *a, CONF_S *b)
{
    PAT_LINE_S *patline_a, *patline_b;

    patline_a = a->d.r.patline;
    patline_b = b->d.r.patline;

    set_pathandle(role_global_flags);
    if(*cur_pat_h)
      (*cur_pat_h)->dirtypinerc = 1;


    if(patline_a->next == patline_b){
	patline_b->prev = patline_a->prev;
	if(patline_a->prev)
	  patline_a->prev->next = patline_b;

	patline_a->next = patline_b->next;
	if(patline_b->next)
	  patline_b->next->prev = patline_a;

	patline_b->next = patline_a;
	patline_a->prev = patline_b;
    }
    else{
	PAT_LINE_S *new_a_prev, *new_a_next;

	new_a_prev = patline_b->prev;
	new_a_next = patline_b->next;

	patline_b->prev = patline_a->prev;
	patline_b->next = patline_a->next;
	if(patline_b->prev)
	  patline_b->prev->next = patline_b;
	if(patline_b->next)
	  patline_b->next->prev = patline_b;

	patline_a->prev = new_a_prev;
	patline_a->next = new_a_next;
	if(patline_a->prev)
	  patline_a->prev->next = patline_a;
	if(patline_a->next)
	  patline_a->next->prev = patline_a;
    }


    if(patline_b->prev == NULL && *cur_pat_h)
      (*cur_pat_h)->patlinehead = patline_b;


    b->prev = a->prev;
    if(a->prev)
      a->prev->next = b;

    a->next = b->next;
    if(b->next)
      b->next->prev = a;

    b->next = a;
    a->prev = b;
}
