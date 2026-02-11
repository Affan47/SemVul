util_keymap_remove_all(struct keymap *map, void *user)
{
   struct cso_hash_iter iter;
   struct keymap_item *item;

   assert(map);
   if (!map)
      return;

   iter = cso_hash_first_node(map->cso);
   while (!cso_hash_iter_is_null(iter)) {
      item = (struct keymap_item *)
         cso_hash_take(map->cso, cso_hash_iter_key(iter));
      map->delete_func(map, item->key, item->value, user);
      FREE(item->key);
      FREE(item);
      iter = cso_hash_first_node(map->cso);
   }
}
