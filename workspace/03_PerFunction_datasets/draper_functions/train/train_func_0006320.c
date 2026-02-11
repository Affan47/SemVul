vocab_get_suffices(resource_mgr_t *resmgr, int *suffices_nr)
{
  int counter = 0;
  suffix_t **suffices;
  resource_t *resource = scir_find_resource(resmgr, sci_vocab, VOCAB_RESOURCE_SUFFIX_VOCAB, 1);
  unsigned int seeker = 1;

  if (!resource) {
    fprintf(stderr,"Could not find suffix vocabulary!\n");
    return NULL;
  }

  suffices = (suffix_t**)sci_malloc(sizeof(suffix_t *));

  while ((seeker < resource->size-1) && (resource->data[seeker + 1] != 0xff)) {

    char *alt_suffix = (char *) resource->data + seeker;
    int alt_len = strlen(alt_suffix);
    char *word_suffix;
    int word_len;

    suffices = (suffix_t**)sci_realloc(suffices, sizeof(suffix_t *) * (counter + 1));

    seeker += alt_len + 1;
    word_suffix = (char *) resource->data + seeker + 3;
    word_len = strlen(word_suffix);

    suffices[counter] = (suffix_t*)sci_malloc(sizeof(suffix_t));


    suffices[counter]->word_suffix = word_suffix;
    suffices[counter]->alt_suffix = alt_suffix;

    suffices[counter]->alt_suffix_length = alt_len;
    suffices[counter]->word_suffix_length = word_len;
    suffices[counter]->class_mask = inverse_16(getInt16(resource->data + seeker));

    seeker += word_len + 4;
    suffices[counter]->result_class = inverse_16(getInt16(resource->data + seeker));
    seeker += 3;

    ++counter;

  }

  *suffices_nr = counter;
  return suffices;
}
