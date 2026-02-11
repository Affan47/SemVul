compute_theoritical_f_nu( void )
{


  ae_genetic_unit* chromosome = get_genetic_unit_list()->get_first()->get_obj();
  int32_t L       = chromosome->get_dna()->get_length();
  int32_t N_G     = chromosome->get_nb_neutral_regions();
  int32_t* b_i    = chromosome->get_beginning_neutral_regions();
  int32_t* e_i    = chromosome->get_end_neutral_regions();
  int32_t lambda  = chromosome->get_nb_bases_in_neutral_regions();
  int32_t l       = L - lambda;

  int32_t* lambda_i = NULL;
  if ( N_G > 0 )
  {
    lambda_i = new int32_t [ N_G ];

    for ( int32_t i = 0; i < N_G - 1; i++)
    {
      lambda_i[i] = e_i[i] - b_i[i] + 1;
    }
    if ( b_i[N_G-1] > e_i[N_G-1] )
    {
      lambda_i[N_G-1] = ( e_i[N_G-1] + L ) - b_i[N_G-1] + 1;
    }
    else
    {
      lambda_i[N_G-1] = e_i[N_G-1] - b_i[N_G-1] + 1;
    }
  }


  double Fv = 1;


  double nu_local_mutation = 1 - ((double) l)/L;
  Fv  = pow( 1 - get_point_mutation_rate()  * ( 1 - nu_local_mutation ), L);
  Fv *= pow( 1 - get_small_insertion_rate() * ( 1 - nu_local_mutation ), L);
  Fv *= pow( 1 - get_small_deletion_rate()  * ( 1 - nu_local_mutation ), L);


  double nu_inversion = nu_local_mutation * nu_local_mutation;
  Fv *= pow( 1 - get_inversion_rate()       * ( 1 - nu_inversion )     , L);


  Fv *= pow( 1 - get_translocation_rate()   * ( 1 - nu_inversion * nu_local_mutation ), L);


  double nu_deletion = 0;
  for ( int32_t i = 0; i < N_G; i++) { nu_deletion += lambda_i[i] * (lambda_i[i] + 1); }
  nu_deletion /= ((double) 2*L*L);
  Fv *= pow( 1 - get_deletion_rate()        * ( 1 - nu_deletion )      , L);


  Fv *= pow( 1 - get_duplication_rate()     * ( 1 - nu_deletion * nu_local_mutation ), L);

  if ( lambda_i != NULL ) delete [] lambda_i;

  return Fv;
}
