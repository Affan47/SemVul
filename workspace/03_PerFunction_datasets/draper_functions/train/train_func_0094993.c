gitem_link_delete_list(
  gitem_link* head,
  bool        rm_elems
) { PROFILE(GITEM_LINK_DELETE_LIST);

  gitem_link* tmp;

  while( head != NULL ) {

    tmp  = head;
    head = tmp->next;


    gen_item_dealloc( tmp->gi, rm_elems );


    free_safe( tmp, sizeof( gitem_link ) );

  }

  PROFILE_END;

}
