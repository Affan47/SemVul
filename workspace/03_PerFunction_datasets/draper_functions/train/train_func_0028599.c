bp_open(bp_db_t* tree, const char* filename) {
  int ret;

  ret = bp__rwlock_init(&tree->rwlock);
  if (ret != BP_OK) return ret;

  ret = bp__writer_create((bp__writer_t*) tree, filename);
  if (ret != BP_OK) goto fatal;

  tree->head.page = NULL;

  ret = bp__init(tree);
  if (ret != BP_OK) goto fatal;

  return BP_OK;

fatal:
  bp__rwlock_destroy(&tree->rwlock);
  return ret;
}
