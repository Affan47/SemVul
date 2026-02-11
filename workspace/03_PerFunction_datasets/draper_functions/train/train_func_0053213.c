SymTable_print (SymTable *st) {
  int i;

  printf ("Table (size: %d)\n", st->size);

  for (i = 0; i < st->size; i++)
    if (st->symbols[i] != NULL) Symbol_print (st->symbols[i]);
}
