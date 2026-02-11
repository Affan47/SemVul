loop_index_limit( int nest, Block **old_floor, int *itaration_times,
		  int *s_index_dep, int *e_index_dep )
{
    int *slimit, *elimit;
    int i, j;
    int *s_flg, *e_flg;
    Block *lp, *lp2;

    i = 0; j = 0;
    slimit = malloc_int_p( nest );
    elimit = malloc_int_p( nest );
    s_flg  = malloc_int_p( nest );
    e_flg  = malloc_int_p( nest );

    for( i = 0; i < nest; i++ ){
	lp = old_floor[i];
	s_index_dep[i] = -1;
	e_index_dep[i] = -1;

	if( lp->loop_info->start.form == NULL ){
	    slimit[i] = lp->loop_info->start.value;
	}else{
	    s_flg[i] = 1;
	    for( j = 0; j < i; j++ ){
		lp2 = old_floor[j];
		if( get_loop_index_operand(lp2)->entry ==
                    lp->loop_info->start.form->entry ){

		    if( s_flg[j] == 0 ){
			slimit[i] = slimit[j]*(lp->loop_info->start.form->sub_a)+
			    (lp->loop_info->start.form->sub_b);
			s_flg[i] = 0;
		    }
		    s_index_dep[i] = j;
		}
	    }
	}
	if( lp->loop_info->end.form == NULL ){
	    elimit[i] = lp->loop_info->end.value;
	}else{
	    e_flg[i] = 1;
	    for( j = 0; j < i; j++ ){
		lp2 = old_floor[j];
		if( get_loop_index_operand(lp2)->entry == lp->loop_info->end.form->
		    entry ){
		    if( e_flg[j] == 0 ){
			elimit[i] = elimit[j]*(lp->loop_info->end.form->sub_a)+
			    (lp->loop_info->end.form->sub_b);
			e_flg[i] = 0;
		    }
		    e_index_dep[i] = j;
		}
	    }
	}
	if( s_flg[i]+e_flg[i] == 0 ){
	    itaration_times[i] = (elimit[i]-slimit[i])/(lp->loop_info->step.value)+1;
	}else{
	    itaration_times[i] = -1;
	}
    }
}
