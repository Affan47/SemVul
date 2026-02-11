_mesa_hash_table_rehash(struct hash_table *ht, int new_size_index)
{
   struct hash_table old_ht;
   struct hash_entry *table, *entry;

   if (new_size_index >= ARRAY_SIZE(hash_sizes))
      return;

   table = rzalloc_array(ht, struct hash_entry,
                         hash_sizes[new_size_index].size);
   if (table == NULL)
      return;

   old_ht = *ht;

   ht->table = table;
   ht->size_index = new_size_index;
   ht->size = hash_sizes[ht->size_index].size;
   ht->rehash = hash_sizes[ht->size_index].rehash;
   ht->max_entries = hash_sizes[ht->size_index].max_entries;
   ht->entries = 0;
   ht->deleted_entries = 0;

   hash_table_foreach(&old_ht, entry) {
      _mesa_hash_table_insert(ht, entry->hash,
                              entry->key, entry->data);
   }

   ralloc_free(old_ht.table);
}
