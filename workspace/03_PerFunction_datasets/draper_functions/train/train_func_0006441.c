divide_activate( void )
{
  if( !memory_allocated ) {
    int i, j;
    libspectrum_byte *memory =
      memory_pool_allocate_persistent( DIVIDE_PAGES * DIVIDE_PAGE_LENGTH, 1 );

    for( i = 0; i < DIVIDE_PAGES; i++ ) {
      divide_ram[i] = memory + i * DIVIDE_PAGE_LENGTH;
      for( j = 0; j < MEMORY_PAGES_IN_8K; j++ ) {
        memory_page *page = &divide_memory_map_ram[i][j];
        page->page = divide_ram[i] + j * MEMORY_PAGE_SIZE;
        page->offset = j * MEMORY_PAGE_SIZE;
      }
    }

    divide_eprom = memory_pool_allocate_persistent( DIVIDE_PAGE_LENGTH, 1 );
    for( i = 0; i < MEMORY_PAGES_IN_8K; i++ ) {
      memory_page *page = &divide_memory_map_eprom[i];
      page->page = divide_eprom + i * MEMORY_PAGE_SIZE;
      page->offset = i * MEMORY_PAGE_SIZE;
    }

    memory_allocated = 1;
  }
}
