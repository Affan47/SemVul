exp_del_nth(EXPANDED_S *exp_head, a_c_arg_t n)
{
    register EXPANDED_S *e;
    int delete_when_done = 0;
    adrbk_cntr_t nn;

    nn = (adrbk_cntr_t)n;
    if(!exp_head)
      panic("exp_head not set in exp_del_nth");

    e = exp_head->next;
    while(e && e->ent < nn)
      e = e->next;

    if(e){
	if(e->ent == nn){
	    delete_when_done++;
	    e = e->next;
	}

	while(e){
	    e->ent--;
	    e = e->next;
	}

	if(delete_when_done)
	  exp_unset_expanded(exp_head, n);
    }
}
