_mesa_search_program_cache(struct gl_program_cache *cache,
                           const void *key, GLuint keysize)
{
   if (cache->last &&
       cache->last->keysize == keysize &&
       memcmp(cache->last->key, key, keysize) == 0) {
      return cache->last->program;
   }
   else {
      const GLuint hash = hash_key(key, keysize);
      struct cache_item *c;

      for (c = cache->items[hash % cache->size]; c; c = c->next) {
         if (c->hash == hash &&
             c->keysize == keysize &&
             memcmp(c->key, key, keysize) == 0) {

            cache->last = c;
            return c->program;
         }
      }

      return NULL;
   }
}
