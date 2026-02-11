count_errors()
  {
  bool good = true;
  errors = 0;

  for( int i = 0; i < sblocks(); ++i )
    {
    const Sblock & sb = sblock( i );
    if( !domain().includes( sb ) )
      { if( domain() < sb ) break; else { good = true; continue; } }
    switch( sb.status() )
      {
      case Sblock::non_tried:
      case Sblock::finished:   good = true; break;
      case Sblock::non_trimmed:
      case Sblock::non_split:
      case Sblock::bad_sector: if( good ) { good = false; ++errors; } break;
      }
    }
  }
