RFG_Regions_init()
{
  RFG_Regions* ret;


  if( !( ret = ( RFG_Regions* )calloc( 1, sizeof( RFG_Regions ) ) ) )
    return NULL;


  if( !stack_init( &(ret->stack) ) )
  {
    free( ret );
    return NULL;
  }


  if( !( ret->filter = RFG_Filter_init() ) )
  {
    free( ret );
    return NULL;
  }


  if( !( ret->groups = RFG_Groups_init() ) )
  {
    free( ret );
    return NULL;
  }

  return ret;
}
