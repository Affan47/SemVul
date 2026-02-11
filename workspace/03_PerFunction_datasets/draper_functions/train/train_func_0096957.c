dump_symbol_table( libspectrum_tape_generalised_data_symbol_table *table )
{
  size_t i, j;

  libspectrum_byte pulses =
    libspectrum_tape_generalised_data_symbol_table_max_pulses( table );
  libspectrum_word symbols =
    libspectrum_tape_generalised_data_symbol_table_symbols_in_table( table );

  printf("    Symbols in block: %ld\n", (unsigned long)libspectrum_tape_generalised_data_symbol_table_symbols_in_block( table ) );
  printf("    Max pulses: %d\n", pulses );
  printf("    Symbols in table: %d\n", symbols );

  for( i = 0; i < symbols; i++ ) {

    libspectrum_tape_generalised_data_symbol *symbol =
      libspectrum_tape_generalised_data_symbol_table_symbol( table, i );

    printf("      Symbol %lu: type %d; pulse lengths: ", (unsigned long)i, libspectrum_tape_generalised_data_symbol_type( symbol ) );

    for( j = 0; j < pulses; j++ )
      printf( "%d ", libspectrum_tape_generalised_data_symbol_pulse( symbol, j ) );

    printf( "\n" );

  }

}
