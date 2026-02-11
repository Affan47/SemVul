Init_System( reax_system *system, control_params *control, char *msg )
{
  int i;
  reax_atom *atom;

  int mincap = system->mincap;
  double safezone = system->safezone;
  double saferzone = system->saferzone;


  system->local_cap = MAX( (int)(system->n * safezone), mincap);
  system->total_cap = MAX( (int)(system->N * safezone), mincap);


  system->numH = 0;
  if( control->hbond_cut > 0 )
    for( i = 0; i < system->n; ++i ) {
      atom = &(system->my_atoms[i]);
      if( system->reax_param.sbp[ atom->type ].p_hbond == 1 )
        atom->Hindex = system->numH++;
      else atom->Hindex = -1;
    }
  system->Hcap = (int)(MAX( system->numH * saferzone, mincap ));

#if defined(DEBUG_FOCUS)
  fprintf( stderr, "p%d: n=%d local_cap=%d\n",
           system->my_rank, system->n, system->local_cap );
  fprintf( stderr, "p%d: N=%d total_cap=%d\n",
           system->my_rank, system->N, system->total_cap );
  fprintf( stderr, "p%d: numH=%d H_cap=%d\n",
           system->my_rank, system->numH, system->Hcap );
#endif

  return SUCCESS;
}
