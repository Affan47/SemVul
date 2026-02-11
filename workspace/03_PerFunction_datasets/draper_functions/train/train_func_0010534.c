update_pokefinder( void )
{
  size_t page, offset, bank, bank_offset;
  gchar buffer[256], *possible_text[2] = { &buffer[0], &buffer[128] };
  GtkTreeIter iter;

  gtk_list_store_clear( GTK_LIST_STORE( location_model ) );

  if( pokefinder_count && pokefinder_count <= MAX_POSSIBLE ) {

    size_t which;

    which = 0;

    for( page = 0; page < MEMORY_PAGES_IN_16K * SPECTRUM_RAM_PAGES; page++ ) {
      memory_page *mapping = &memory_map_ram[page];
      bank = mapping->page_num;

      for( offset = 0; offset < MEMORY_PAGE_SIZE; offset++ )
	if( ! (pokefinder_impossible[page][offset/8] & 1 << (offset & 7)) ) {
	  bank_offset = mapping->offset + offset;

	  possible_page[ which ] = bank;
	  possible_offset[ which ] = bank_offset;
	  which++;

	  snprintf( possible_text[0], 128, "%lu", (unsigned long)bank );
	  snprintf( possible_text[1], 128, "0x%04X", (unsigned)bank_offset );


	  gtk_list_store_append( GTK_LIST_STORE( location_model ), &iter );
	  gtk_list_store_set( GTK_LIST_STORE( location_model ), &iter,
	                      COL_PAGE, possible_text[0],
	                      COL_OFFSET, possible_text[1],
	                      -1 );
	}
    }

    gtk_widget_show( location_list );

  } else {
    gtk_widget_hide( location_list );
  }

  snprintf( buffer, 256, "Possible locations: %lu",
	    (unsigned long)pokefinder_count );
  gtk_label_set_text( GTK_LABEL( count_label ), buffer );
}
