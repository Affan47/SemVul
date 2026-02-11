cf_hash_destroy(cf_hash_t *hsh) {
  cf_hash_keylist_t *key,*key1;
  ub4 hval,hval_short;
  cf_hash_entry_t *ent;
  size_t keylen;

  for(key=hsh->keys.elems;key;key=key1) {
    keylen     = strlen((char *)key->key);
    hval       = lookup(key->key,keylen,0);
    hval_short = hval & cf_hashmask(hsh->tablesize);

    key1 = key->next;

    if(hsh->table[hval_short]) {
      for(ent = hsh->table[hval_short];ent && (ent->hashval != hval || ent->keylen != keylen || memcmp(ent->key,key->key,keylen) != 0);ent=ent->next);

      if(ent) {
        if(ent->stat == 0) {
          if(hsh->destroy) hsh->destroy(ent->data);
          free(ent->data);
        }
        free(ent->key);

        if(ent->prev) ent->prev->next = ent->next;
        else hsh->table[hval_short] = ent->next;

        if(ent->next) ent->next->prev = ent->prev;

        if(ent->keyelem->next) ent->keyelem->next->prev = ent->keyelem->prev;
        if(ent->keyelem->prev) ent->keyelem->prev->next = ent->keyelem->next;

        free(ent->keyelem);

        free(ent);
        hsh->elements--;
      }
    }
  }

  free(hsh->table);
  free(hsh);
}
