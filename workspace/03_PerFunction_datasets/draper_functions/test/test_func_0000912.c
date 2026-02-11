hash_table_clear(struct hash_table *ht)
{
   struct node *node;
   struct node *temp;
   unsigned i;


   for (i = 0; i < ht->num_buckets; i++) {
      foreach_s(node, temp, & ht->buckets[i]) {
	 remove_from_list(node);
	 free(node);
      }

      assert(is_empty_list(& ht->buckets[i]));
   }
}
