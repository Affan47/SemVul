vsignal_db_read(
  char**     line,
  func_unit* curr_funit
) { PROFILE(VSIGNAL_DB_READ);

  char         name[256];
  vsignal*     sig;
  vector*      vec;
  int          id;
  int          sline;
  unsigned int pdim_num;
  unsigned int udim_num;
  dim_range*   dim    = NULL;
  ssuppl       suppl;
  int          chars_read;
  unsigned int i;


  if( sscanf( *line, "%s %d %d %x %u %u%n", name, &id, &sline, &(suppl.all), &pdim_num, &udim_num, &chars_read ) == 6 ) {

    *line = *line + chars_read;


    dim = (dim_range*)malloc_safe( sizeof( dim_range ) * (pdim_num + udim_num) );

    Try {


      i = 0;
      while( i < (pdim_num + udim_num) ) {
        if( sscanf( *line, " %d %d%n", &(dim[i].msb), &(dim[i].lsb), &chars_read ) == 2 ) {
          *line = *line + chars_read;
        } else {
          print_output( "Unable to parse signal line in database file.  Unable to read.", FATAL, __FILE__, __LINE__ );
          Throw 0;
        }
        i++;
      }


      vector_db_read( &vec, line );

    } Catch_anonymous {
      free_safe( dim, sizeof( dim_range ) );
      Throw 0;
    }


    sig = vsignal_create( name, suppl.part.type, vec->width, sline, suppl.part.col );
    sig->id                    = id;
    sig->suppl.part.assigned   = suppl.part.assigned;
    sig->suppl.part.mba        = suppl.part.mba;
    sig->suppl.part.big_endian = suppl.part.big_endian;
    sig->suppl.part.excluded   = suppl.part.excluded;
    sig->pdim_num              = pdim_num;
    sig->udim_num              = udim_num;
    sig->dim                   = dim;


    vector_dealloc( sig->value );
    sig->value = vec;


    if( curr_funit == NULL ) {
      print_output( "Internal error:  vsignal in database written before its functional unit", FATAL, __FILE__, __LINE__ );
      Throw 0;
    } else {
      sig_link_add( sig, &(curr_funit->sig_head), &(curr_funit->sig_tail) );
    }

  } else {

    print_output( "Unable to parse signal line in database file.  Unable to read.", FATAL, __FILE__, __LINE__ );
    Throw 0;

  }

  PROFILE_END;

}
