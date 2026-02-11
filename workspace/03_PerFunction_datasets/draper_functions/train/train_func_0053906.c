main( const int argc, const char * const argv[] )
  {
  int argind;
  bool loose = false;
  const struct ap_Option options[] =
    {
    { 'G', "traditional",       ap_no  },
    { 'h', "help",              ap_no  },
    { 'l', "loose-exit-status", ap_no  },
    { 'p', "prompt",            ap_yes },
    { 'r', "restricted",        ap_no  },
    { 's', "quiet",             ap_no  },
    { 's', "silent",            ap_no  },
    { 'v', "verbose",           ap_no  },
    { 'V', "version",           ap_no  },
    {  0 ,  0,                  ap_no } };

  struct Arg_parser parser;
  invocation_name = argv[0];

  if( !ap_init( &parser, argc, argv, options, 0 ) )
    { show_error( "Memory exhausted.", 0, false ); return 1; }
  if( ap_error( &parser ) )
    { show_error( ap_error( &parser ), 0, true ); return 1; }

  for( argind = 0; argind < ap_arguments( &parser ); ++argind )
    {
    const int code = ap_code( &parser, argind );
    const char * const arg = ap_argument( &parser, argind );
    if( !code ) break;
    switch( code )
      {
      case 'G': traditional_ = true; break;
      case 'h': show_help(); return 0;
      case 'l': loose = true; break;
      case 'p': set_prompt( arg ); break;
      case 'r': restricted_ = true; break;
      case 's': scripted_ = true; break;
      case 'v': set_verbose(); break;
      case 'V': show_version(); return 0;
      default : show_error( "internal error: uncaught option.", 0, false );
                return 3;
      }
    }
  setlocale( LC_ALL, "" );
  if( !init_buffers() ) return 1;

  while( argind < ap_arguments( &parser ) )
    {
    const char * const arg = ap_argument( &parser, argind );
    if( !strcmp( arg, "-" ) ) { scripted_ = true; ++argind; continue; }
    if( may_access_filename( arg ) )
      {
      if( read_file( arg, 0 ) < 0 && is_regular_file( 0 ) )
        return 2;
      else if( arg[0] != '!' ) set_def_filename( arg );
      }
    else
      {
      fputs( "?\n", stderr );
      if( arg[0] ) set_error_msg( "Invalid filename" );
      if( is_regular_file( 0 ) ) return 2;
      }
    break;
    }
  ap_free( &parser );

  return main_loop( loose );
  }
