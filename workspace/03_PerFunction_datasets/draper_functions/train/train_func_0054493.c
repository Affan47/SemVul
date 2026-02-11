xsh_linetilt_list_add( xsh_linetilt_list * list,
			    xsh_linetilt * line, int idx )
{
  XSH_ASSURE_NOT_NULL( list ) ;
  XSH_ASSURE_NOT_NULL( line ) ;
  list->list[idx] = line ;
  list->size++ ;
 cleanup:
  return ;
}
