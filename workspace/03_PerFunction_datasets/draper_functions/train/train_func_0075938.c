volume_restore ARGS2((stepsize,mode),
REAL stepsize,
int mode)
{ body_id bi_id;
  struct gen_quant *gq;
  int i,k;
  int fixi;

  if ( itdebug )
    outstring("volume_restore()\n");

  if ( !fixed_constraint_flag ) return;

  vol_deficit = (REAL*)temp_calloc(maxquants,sizeof(REAL));
  vol_restore = (REAL*)temp_calloc(maxquants,sizeof(REAL));


  if ( !web.pressure_flag && !everything_quantities_flag )
    FOR_ALL_BODIES(bi_id)
     {
       if ( !(get_battr(bi_id) & FIXEDVOL) ) continue;
       fixi = get_body_fixnum(bi_id);
       if ( fixi < 0 ) continue;
       vol_deficit[fixi] = get_body_fixvol(bi_id) - get_body_volume(bi_id);
     }
  for ( k = 0 ; k < gen_quant_count ; k++ )
  { gq = GEN_QUANT(k);
    if ( !(gq->flags & Q_FIXED) ) continue;
    if ( valid_id(gq->b_id) && web.pressure_flag ) continue;
    fixi = gq->fixnum;
    if ( fixi < 0 ) continue;
    vol_deficit[fixi] = gq->target - gq->value;
  }


  if ( sparse_constraints_flag )
  { if ( LS.A == NULL ) calc_leftside();
    ysmp_solve(&LS,vol_deficit,vol_restore);
    free_system(&LS);
  }
  else
  { if ( rleftside == NULL ) calc_leftside();
    LD_solve(rleftside,vol_deficit,vol_restore,fixcount);
  }


  if ( optparamcount )
    for ( i = 0 ; i < optparamcount ; i++ )
     for ( k = 0 ; k < gen_quant_count ; k++ )
     { int fixk = GEN_QUANT(k)->fixnum;
       int volk = GEN_QUANT(k)->vol_number;
       if ( fixk >= 0 )
          globals(optparam[i].pnum)->value.real += vol_restore[fixk]
            *globals(optparam[i].pnum)->attr.varstuff.pscale*optparam_congrads[i][volk];
     }

  #ifdef MPI_EVOLVER
  mpi_volume_restore(maxquants,stepsize,mode);
  #else
  local_volume_restore(stepsize,mode);
  #endif

  partner_move();

  if ( vol_deficit ) temp_free((char *)vol_deficit);  vol_deficit = NULL;
  if ( vol_restore ) temp_free((char *)vol_restore);  vol_restore = NULL;

}
