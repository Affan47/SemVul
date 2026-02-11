copy_non_tried()
  {
  bool first_post = true;

  for( bool first_pass = true; ; first_pass = false )
    {
    long long pos = 0;
    int skip_size = 0;
    bool block_found = false;

    if( first_pass && current_status() == copying &&
        domain().includes( current_pos() ) )
      {
      Block b( current_pos(), 1 );
      find_chunk( b, Sblock::non_tried );
      if( b.size() > 0 ) pos = b.pos();
      }

    while( pos >= 0 )
      {
      const int alignment = ( skip_size ? hardbs() : softbs() );
      Block b( pos, alignment );
      find_chunk( b, Sblock::non_tried, alignment );
      if( b.size() <= 0 ) break;
      if( pos != b.pos() ) skip_size = 0;
      pos = b.end();
      current_status( copying );
      block_found = true;
      const Sblock::Status st =
        ( ( b.size() > hardbs() ) ? Sblock::non_trimmed : Sblock::bad_sector );
      int copied_size = 0, error_size = 0;
      const int retval = copy_and_update( b, st, copied_size, error_size,
                                          "Copying non-tried blocks...",
                                          first_post, true );
      if( error_size > 0 ) errsize += error_size;
      else if( skip_size > 0 && copied_size > 0 )
        { skip_size -= copied_size; if( skip_size < 0 ) skip_size = 0; }
      if( retval ) return retval;
      if( error_size > 0 ) error_rate += error_size;
      update_rates();
      if( error_size > 0 || slow_read() )
        {
        if( pos >= 0 && skip_size > 0 )
          {
          b.assign( pos, skip_size ); b.fix_size();
          find_chunk( b, Sblock::non_tried );
          if( pos == b.pos() && b.size() > 0 )
            {
            if( error_size > 0 )
              { errors += change_chunk_status( b, Sblock::non_trimmed );
                errsize += b.size(); }
            pos = b.end();
            }
          }
        if( skip_size < skipbs ) skip_size = skipbs;
        else if( skip_size <= max_skip_size / 2 ) skip_size *= 2;
        else skip_size = max_skip_size;
        }
      if( !update_logfile( odes_ ) ) return -2;
      }
    if( !block_found ) break;
    reduce_min_read_rate();
    }
  return 0;
  }
