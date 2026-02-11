xsh_linetilt_list_new( int size,
					   cpl_propertylist * header )
{
  xsh_linetilt_list * result = NULL ;

  XSH_ASSURE_NOT_NULL( header ) ;


  check( result = cpl_malloc( sizeof( xsh_linetilt_list ) ) ) ;
  memset( result, 0, sizeof( xsh_linetilt_list ) ) ;

  check( result->list = cpl_malloc( sizeof( xsh_linetilt * ) * size ) ) ;
  memset( result->list, 0, sizeof( xsh_linetilt * )*size ) ;
  result->full_size = size ;
  result->header = header ;

 cleanup:
  return result ;
}
