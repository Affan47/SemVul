mindex_free(Mindex mdx)
{
  if (!mindex_empty(mdx))
    fprintf(stderr, "WARNING, mindex_free called with nonempty mindex.\n");
  else {
    switch (mdx->index_type) {
    case FPA:
      zap_fpa_index(mdx->fpa);
      break;
    case LINEAR:
      break;
    case DISCRIM_WILD:
    case DISCRIM_BIND:
      discrim_dealloc(mdx->discrim_tree);
      break;
    }
    free_mindex(mdx);
  }
}
