gitem_link_remove(
            gen_item*    gi,
   gitem_link** head,
   gitem_link** tail
) { PROFILE(GITEM_LINK_REMOVE);

  gitem_link* gil;
  gitem_link* last;

  gil = *head;
  while( (gil != NULL) && (gil->gi != gi) ) {
    last = gil;
    gil  = gil->next;
  }

  if( gil != NULL ) {

    if( (gil == *head) && (gil == *tail) ) {
      *head = *tail = NULL;
    } else if( gil == *head ) {
      *head = gil->next;
    } else if( gil == *tail ) {
      last->next = NULL;
      *tail      = last;
    } else {
      last->next = gil->next;
    }

    free_safe( gil, sizeof( gitem_link ) );

  }

  PROFILE_END;

}
