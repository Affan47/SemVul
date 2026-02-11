remove_non_coding_bases( void)
{
  ae_environment* env = _exp_m->get_env() ;

  reset_expression();
  locate_promoters();
  _distance_to_target_computed        = false;
  _fitness_computed                   = false;
  compute_phenotypic_contribution();
  if(_exp_m->get_output_m()->get_compute_phen_contrib_by_GU())
  {
    compute_distance_to_target(env);
  }
  compute_fitness(env);
  double initial_fitness = get_fitness();

  int32_t genome_length = _dna->get_length();
  bool* belongs_to_coding_RNA = is_belonging_to_coding_RNA();

  int32_t non_coding_bases_nb = get_nb_bases_in_0_coding_RNA();
  int32_t start = 0;
  int32_t end = 0;


  for ( int32_t i = genome_length-1 ; i >= 0 ; i-- )
  {
    if ( belongs_to_coding_RNA[i] == false )
    {
      end = i+1;
      while((i-1) >=0 && belongs_to_coding_RNA[(i-1)] == false )
      {
        i--;
      }
      start = i;
      _dna->remove(start,end);

      locate_promoters();
      reset_expression();
      _distance_to_target_computed        = false;
      _fitness_computed                   = false;
      compute_phenotypic_contribution();
      if(_exp_m->get_output_m()->get_compute_phen_contrib_by_GU())
      {
        compute_distance_to_target(env);
      }
      compute_fitness(env);
      assert(get_fitness()==initial_fitness);

      _non_coding_computed = false;
      non_coding_bases_nb = get_nb_bases_in_0_coding_RNA();
    }
  }

  locate_promoters();
  reset_expression();
  _distance_to_target_computed        = false;
  _fitness_computed                   = false;
  compute_phenotypic_contribution();
  if(_exp_m->get_output_m()->get_compute_phen_contrib_by_GU())
  {
    compute_distance_to_target(env);
  }
  compute_fitness(env);
  assert(get_fitness()==initial_fitness);

  _non_coding_computed = false;
  non_coding_bases_nb = get_nb_bases_in_0_coding_RNA();
  assert(non_coding_bases_nb==0);

  delete [] belongs_to_coding_RNA;
}
