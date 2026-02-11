cf_hash_new(cf_hash_cleanup_t cl) {
  cf_hash_t *hsh = malloc(sizeof(cf_hash_t));
  ub4 elems = cf_hashsize(CF_HASH_SIZE);

  if(!hsh) return NULL;

  hsh->elements = 0;


  hsh->tablesize = CF_HASH_SIZE;


  hsh->table     = calloc(elems,sizeof(cf_hash_entry_t **));

  hsh->destroy   = cl;

  hsh->keys.elems = hsh->keys.last = NULL;

  return hsh;
}
