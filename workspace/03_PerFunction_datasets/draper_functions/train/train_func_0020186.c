hash_table_insert(char *key_file, time_t mtime,
			     SSL_CTX *ssl_ctx)
{
   int level, split;
   uint32_t hash = str_hash(key_file);
   size_t bucket;
   int do_split = 0;
   struct bucket *el;
   struct bucket *new_bucket_el;

   split = ht.split;
   level = ht.level;

   bucket = hash & ((1 << level) - 1);
   if (bucket < split)
      bucket = hash & ((1 << (level + 1)) - 1);

   el = ht.buckets[bucket];
   while (el != NULL) {
      if (el->hash == hash && strcmp(el->key_file, key_file) == 0) {
	 el->mtime = mtime;
	 if (el->ssl_ctx != NULL)
	    SSL_CTX_free(el->ssl_ctx);
	 el->ssl_ctx = ssl_ctx;
	 break;
      }
      el = el->next;
   }

   if (el == NULL) {
      if (ht.buckets[bucket] != NULL)
	 do_split = !0;

      new_bucket_el = (struct bucket *)driver_alloc(sizeof(struct bucket));
      new_bucket_el->hash = hash;
      new_bucket_el->key_file = (char *)driver_alloc(strlen(key_file) + 1);
      strcpy(new_bucket_el->key_file, key_file);
      new_bucket_el->mtime = mtime;
      new_bucket_el->ssl_ctx = ssl_ctx;
      new_bucket_el->next = ht.buckets[bucket];
      ht.buckets[bucket] = new_bucket_el;
   }

   if (do_split) {
      struct bucket **el_ptr = &ht.buckets[split];
      size_t new_bucket = split + (1 << level);
      while (*el_ptr != NULL) {
	 uint32_t hash = (*el_ptr)->hash;
	 if ((hash & ((1 << (level + 1)) - 1)) == new_bucket) {
	    struct bucket *moved_el = *el_ptr;
	    *el_ptr = (*el_ptr)->next;
	    moved_el->next = ht.buckets[new_bucket];
	    ht.buckets[new_bucket] = moved_el;
	 } else
	    el_ptr = &(*el_ptr)->next;
      }
      split++;
      if (split == 1 << level) {
	 size_t size;
	 size_t i;
	 split = 0;
	 level++;
	 size = 1 << (level + 1);
	 ht.split = split;
	 ht.level = level;
	 ht.buckets = (struct bucket **)
	    driver_realloc(ht.buckets, sizeof(struct bucket *) * size);
	 for (i = 1 << level; i < size; i++)
	    ht.buckets[i] = NULL;
      } else
	 ht.split = split;
   }
}
