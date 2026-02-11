load( gzFile backup_file )
{


  int16_t nb_gaussians;
  gzread( backup_file, &nb_gaussians, sizeof(nb_gaussians) );
  if ( nb_gaussians > 0 ) _gaussians = new ae_list<ae_gaussian*>();
  for ( int16_t i = 0 ; i < nb_gaussians ; i++ )
  {
    _gaussians->add( new ae_gaussian( backup_file ) );
  }


  gzread( backup_file, &_sampling, sizeof(_sampling) );


  int16_t nb_custom_points;
  gzread( backup_file, &nb_custom_points, sizeof(nb_custom_points) );
  if ( nb_custom_points > 0 ) _custom_points = new ae_list<ae_point_2d*>();
  for ( int16_t i = 0 ; i < nb_custom_points ; i++ )
  {
    _custom_points->add( new ae_point_2d( backup_file ) );
  }


  for ( int16_t i = 0 ; i < _nb_segments ; i++ )
  {
    delete _segments[i];
  }
  delete [] _segments;


  gzread( backup_file, &_nb_segments, sizeof(_nb_segments) );

  _segments = new ae_env_segment* [_nb_segments];

  for ( int16_t i = 0 ; i < _nb_segments; i++ )
  {
    _segments[i] = new ae_env_segment( backup_file );


  }


  int8_t tmp_var_method;
  gzread( backup_file, &tmp_var_method, sizeof(tmp_var_method) );
  _var_method = (ae_env_var) tmp_var_method;

  if ( _var_method != NO_VAR )
  {
    _var_prng = new ae_jumping_mt( backup_file );
    gzread( backup_file, &_var_sigma, sizeof(_var_sigma) );
    gzread( backup_file, &_var_tau,   sizeof(_var_tau) );
  }


  int8_t tmp_noise_method;
  gzread( backup_file, &tmp_noise_method, sizeof(tmp_noise_method) );
  _noise_method = (ae_env_noise) tmp_noise_method;

  if ( _noise_method != NO_NOISE )
  {
    int8_t tmp_cur_noise_saved;
    gzread( backup_file, &tmp_cur_noise_saved,  sizeof(tmp_cur_noise_saved) );
    if ( tmp_cur_noise_saved )
    {
      _cur_noise  = new ae_fuzzy_set( backup_file );
    }

    _noise_prng = new ae_jumping_mt( backup_file );
    gzread( backup_file, &_noise_alpha, sizeof(_noise_alpha) );
    gzread( backup_file, &_noise_sigma, sizeof(_noise_sigma) );
    gzread( backup_file, &_noise_prob,  sizeof(_noise_prob)  );
    gzread( backup_file, &_noise_sampling_log, sizeof(_noise_sampling_log) );
  }


  if ( _var_method != NO_VAR || is_noise_allowed() )
  {
    int16_t nb_gaussians;
    gzread( backup_file, &nb_gaussians, sizeof(nb_gaussians) );
    if ( nb_gaussians > 0 ) _initial_gaussians = new ae_list<ae_gaussian*>();
    for ( int16_t i = 0 ; i < nb_gaussians ; i++ )
    {
      _initial_gaussians->add( new ae_gaussian( backup_file ) );
    }
  }


  build();
}
