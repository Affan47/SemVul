Save( MemBuffer &file ) const {
  int i;

  file.Write8( e_id );
  file.Write8( e_type );
  file.Write8( e_trigger );
  file.Write8( e_depend );
  file.Write8( e_discard );

  for ( i = 0; i < 3; ++i ) file.Write16( e_tdata[i] );
  for ( i = 0; i < 3; ++i ) file.Write16( e_data[i] );

  file.Write16( e_title );
  file.Write16( e_message );
  file.Write16( e_flags );
  file.Write8( e_player->ID() );
  return 0;
}
