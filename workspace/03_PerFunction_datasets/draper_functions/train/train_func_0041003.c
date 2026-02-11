dump_pilot_repeats( libspectrum_tape_block *block )
{
  size_t i;

  libspectrum_tape_generalised_data_symbol_table *pilot =
    libspectrum_tape_block_pilot_table( block );

  for( i = 0; i < libspectrum_tape_generalised_data_symbol_table_symbols_in_block( pilot ); i++ ) {
    printf( "    Repeat %2lu: symbol %d repeated %d times\n", (unsigned long)i,
	    libspectrum_tape_block_pilot_symbols( block, i ),
	    libspectrum_tape_block_pilot_repeats( block, i ) );
  }
}
