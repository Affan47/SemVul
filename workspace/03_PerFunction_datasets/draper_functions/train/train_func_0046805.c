add_loader_block( libspectrum_tape *tape, libspectrum_byte **loader,
		  libspectrum_snap *snap, const settings_t *settings )
{
  libspectrum_tape_block *block;
  libspectrum_byte *basic;
  size_t length;
  int error2;

  length = basic_length + loader_length + 2;

  *loader = malloc( length * sizeof( libspectrum_byte ) );
  if( !(*loader) ) {
    print_error( "out of memory at %s:%d", __FILE__, __LINE__ );
    return 1;
  }

  block = libspectrum_tape_block_alloc( LIBSPECTRUM_TAPE_BLOCK_ROM );

  libspectrum_tape_block_set_pause( block, 100 );
  libspectrum_tape_block_set_data_length( block, length );
  libspectrum_tape_block_set_data( block, (*loader) );

  (*loader)[0] = 0xff;


  basic = *loader + 1;


  memcpy( basic, SpectrumBASICData, basic_length );


  memcpy( basic + basic_game_name_offset, settings->game_name, 32 );
  memcpy( basic + basic_info1_offset, settings->info1, 32 );
  memcpy( basic + basic_info2_offset, settings->info2, 32 );


  error2 = create_loader( basic + basic_length, snap, settings );
  if( error2 ) { libspectrum_tape_block_free( block ); return error2; }


  libspectrum_tape_append_block( tape, block );

  return 0;
}
