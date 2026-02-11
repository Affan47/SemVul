if2_init( void )
{
  int i;
  int if2_source;

  module_register( &if2_module_info );

  if2_source = memory_source_register( "If2" );
  for( i = 0; i < MEMORY_PAGES_IN_16K; i++ )
    if2_memory_map_romcs[i].source = if2_source;

  periph_register( PERIPH_TYPE_INTERFACE2, &if2_periph );
}
