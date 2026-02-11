xsh_spectralformat_list_free( xsh_spectralformat_list** list)
{
  if ( list && *list){

    if ( ( *list)->list){
      cpl_free( (*list)->list);
    }
    xsh_free_propertylist( &((*list)->header));
    cpl_free( *list);
    *list = NULL;
  }
}
