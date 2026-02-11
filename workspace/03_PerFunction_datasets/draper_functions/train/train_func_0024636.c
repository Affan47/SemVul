xsh_rec_list_free(xsh_rec_list** list)
{
  if (list != NULL && *list != NULL ) {


    int i ;
    xsh_rec_list * plist = NULL;

    plist = *list;


    for (i = 0; i < plist->size; i++) {
      xsh_rec * pr = &(plist->list[i]) ;

      xsh_msg_dbg_high( "Freeing order index %d", i ) ;
      if ( pr == NULL ) continue ;
      xsh_msg_dbg_high( "     Abs Order: %d", pr->order ) ;
      cpl_free( pr->slit ) ;
      cpl_free( pr->lambda ) ;
      cpl_free( pr->data1 ) ;
      cpl_free( pr->errs1 ) ;
      cpl_free( pr->qual1 ) ;
    }
    if ((*list)->list){
      cpl_free((*list)->list);
    }

    xsh_free_propertylist(&((*list)->header));
    cpl_free(*list);
    *list = NULL;
  }
}
