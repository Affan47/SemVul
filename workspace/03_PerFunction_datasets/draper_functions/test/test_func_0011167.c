ds_diction_touch(
  ds_diction_t diction,
  ds_key_t key,
  const char *name,
  int flags)
{
  unsigned long bucket = key % diction->size;
  ds_term_t parent = NULL;
  ds_term_t insert = NULL;
  ds_term_t term;

  term = diction->tbl[bucket];
  while (term) {
    if (key == term->key) {
      insert = term;
      break;
    }
    parent = term;
    term = term->next;
  }

  if (!insert) {
    insert = ds_diction_term_create(key, name);
    if (!insert) {
      perror("ds_diction_touch: ds_diction_term_create() failed");
      return NULL;
    }
    diction->items++;
    if (parent)
      parent->next = insert;
    else
      diction->tbl[bucket] = insert;
  } else {
    if (!insert->name && name)
      insert->name = strdup(name);
    insert->frequency++;
  }

  if (flags & DSD_CONTEXT) {
    if (flags & DSD_CHAINED)
      nt_add(diction->chained_order, insert);
    else
      nt_add(diction->order, insert);
  }

  return insert;
}
