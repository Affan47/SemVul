move_ab_entry(AdrBk *ab, a_c_arg_t move_this_one, a_c_arg_t put_it_before_this)
{
    adrbk_cntr_t m, before;
    AdrBk_Entry  ae_tmp;
    AdrBk_Entry *ae_m, *ae_m_next, *ae_before, *ae_before_prev, *ae_before_next;

    dprint((7, "- move_ab_entry(move_this=%ld,before_this=%ld) -\n", (long) move_this_one, (long) put_it_before_this));

    m      = (adrbk_cntr_t) move_this_one;
    before = (adrbk_cntr_t) put_it_before_this;

    if(!ab || m == NO_NEXT || before == NO_NEXT
       || m == before || m+1 == before || before > ab->count){
	;
    }
    else if(m+1 < before){


	ae_m  = adrbk_get_ae(ab, (a_c_arg_t) m);
	ae_m_next  = adrbk_get_ae(ab, (a_c_arg_t) (m+1));
	ae_before_prev  = adrbk_get_ae(ab, (a_c_arg_t) (before-1));
	if(ae_m && ae_m_next && ae_before_prev){
	    memcpy(&ae_tmp, ae_m, sizeof(ae_tmp));
	    memmove(ae_m, ae_m_next, (before-m-1) * sizeof(ae_tmp));
	    memcpy(ae_before_prev, &ae_tmp, sizeof(ae_tmp));
	}
    }
    else if(m > before){


	ae_m  = adrbk_get_ae(ab, (a_c_arg_t) m);
	ae_before = adrbk_get_ae(ab, (a_c_arg_t) before);
	ae_before_next = adrbk_get_ae(ab, (a_c_arg_t) (before+1));
	if(ae_m && ae_before && ae_before_next){
	    memcpy(&ae_tmp, ae_m, sizeof(ae_tmp));
	    memmove(ae_before_next, ae_before, (m-before) * sizeof(ae_tmp));
	    memcpy(ae_before, &ae_tmp, sizeof(ae_tmp));
	}
    }

    dprint((9, "- move_ab_entry: done -\n"));

    repair_abook_tries(ab);
}
