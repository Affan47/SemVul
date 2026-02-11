list_element_from_data( List *l, void *data ) {
  Element *temp;

  if ( !l || !data || !l->n)
    return NULL;

  temp = l->start.next;

  while ( temp->data != data ) {
    if ( !temp || temp==&l->stop )
      return NULL;
    temp = temp->next;
  }
  return temp;
}
