_mesa_hash_table_random_entry(struct hash_table *ht,
                              bool (*predicate)(struct hash_entry *entry))
{
   struct hash_entry *entry;
   uint32_t i = rand() % ht->size;

   if (ht->entries == 0)
      return NULL;

   for (entry = ht->table + i; entry != ht->table + ht->size; entry++) {
      if (entry_is_present(ht, entry) &&
          (!predicate || predicate(entry))) {
         return entry;
      }
   }

   for (entry = ht->table; entry != ht->table + i; entry++) {
      if (entry_is_present(ht, entry) &&
          (!predicate || predicate(entry))) {
         return entry;
      }
   }

   return NULL;
}
