e_order_clone(const E_Order *eo)
{
   E_Order *eoc;
   Eina_List *l;
   Efreet_Desktop *desktop;

   E_OBJECT_CHECK_RETURN(eo, NULL);
   E_OBJECT_TYPE_CHECK_RETURN(eo, E_ORDER_TYPE, NULL);

   eoc = E_OBJECT_ALLOC(E_Order, E_ORDER_TYPE, _e_order_free);
   if (!eoc) return NULL;

   eoc->path = eina_stringshare_ref(eo->path);
   EINA_LIST_FOREACH(eo->desktops, l, desktop)
     {
        efreet_desktop_ref(desktop);
        eoc->desktops = eina_list_append(eoc->desktops, desktop);
     }
   eoc->monitor = ecore_file_monitor_add(eoc->path, _e_order_cb_monitor, eoc);

   orders = eina_list_append(orders, eoc);
   return eoc;
}
