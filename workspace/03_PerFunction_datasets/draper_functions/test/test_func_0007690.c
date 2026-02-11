avl_insert(struct avl_table *table, void *item)
{
   void **p = avl_probe(table, item);
   return p == NULL || *p == item ? NULL : *p;
}
