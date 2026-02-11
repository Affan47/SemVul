insert(symbol_t* table, entry_t* entry) {
  if ( lookup(*table,entry->name) != NULL ) {
    return -1;
  }
  int bucket = hashpjw(entry->name);
  if ( table->list[bucket] == NULL ) {
    table->list[bucket]=(node*)malloc(sizeof(node));
    table->list[bucket]->next=NULL;
    table->list[bucket]->data=(entry_t*)malloc(sizeof(entry_t));
    *table->list[bucket]->data=*entry;
    return 0;
  }
  node* aux;
  aux = table->list[bucket];
  while (aux->next != NULL) {
    aux = aux->next;
  }
  node* novo;
  novo=(node*)malloc(sizeof(node));
  novo->next=NULL;
  novo->data=(entry_t*)malloc(sizeof(entry_t));
  *novo->data=*entry;
  aux->next=novo;
  return 0;
}
