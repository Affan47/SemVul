_mesa_hash_table_search(struct hash_table *ht, uint32_t hash,
                        const void *key)
{
   uint32_t start_hash_address = hash % ht->size;
   uint32_t hash_address = start_hash_address;

   do {
      uint32_t double_hash;

      struct hash_entry *entry = ht->table + hash_address;

      if (entry_is_free(entry)) {
         return NULL;
      } else if (entry_is_present(ht, entry) && entry->hash == hash) {
         if (ht->key_equals_function(key, entry->key)) {
            return entry;
         }
      }

      double_hash = 1 + hash % ht->rehash;

      hash_address = (hash_address + double_hash) % ht->size;
   } while (hash_address != start_hash_address);

   return NULL;
}
