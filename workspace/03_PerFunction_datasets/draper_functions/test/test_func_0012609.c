vocab_free_suffices(resource_mgr_t *resmgr, suffix_t **suffices, int suffices_nr)
{
  int i;

  scir_unlock_resource(resmgr, scir_find_resource(resmgr, sci_vocab, VOCAB_RESOURCE_SUFFIX_VOCAB, 0),
		       VOCAB_RESOURCE_SUFFIX_VOCAB, sci_vocab);

  for (i = 0; i < suffices_nr; i++)
    free(suffices[i]);

  free(suffices);
}
