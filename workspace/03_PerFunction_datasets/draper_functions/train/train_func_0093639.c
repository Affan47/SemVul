chash_new(unsigned int size, int flags)
{
  chash * h;

  h = (chash *) malloc(sizeof(chash));
  if (h == NULL)
    return NULL;

  h->count = 0;
  h->cells = (struct chashcell **) calloc(size, sizeof(struct chashcell *));
  if (h->cells == NULL) {
    free(h);
    return NULL;
  }
  h->size = size;
  h->copykey = flags & CHASH_COPYKEY;
  h->copyvalue = flags & CHASH_COPYVALUE;

  return h;
}
