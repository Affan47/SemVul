e_order_new(const char *path)
{
   E_Order *eo;

   eo = E_OBJECT_ALLOC(E_Order, E_ORDER_TYPE, _e_order_free);
   if (!eo) return NULL;

   if (path) eo->path = eina_stringshare_add(path);
   _e_order_read(eo);
   eo->monitor = ecore_file_monitor_add(path, _e_order_cb_monitor, eo);

   orders = eina_list_append(orders, eo);

   return eo;
}
