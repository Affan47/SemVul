_e_menu_item_activate_char(const char *key_compose)
{
   E_Menu *m;
   E_Menu_Item *mi;
   Eina_List *ll, *ll_orig;


   if (!key_compose) return;


   m = _e_menu_active_get();
   if (!m)
     {
        if (!_e_active_menus) return;
        m = eina_list_data_get(_e_active_menus);
        if (!m) return;
     }

   ll = _e_menu_list_item_active_get();

   if (!ll)
     {
        ll = m->items;
        mi = eina_list_data_get(ll);

        if (!mi->separator && mi->label && !strncasecmp(key_compose, mi->label, strlen(key_compose)))
          {
             e_menu_item_active_set(mi, 1);
             _e_menu_item_ensure_onscreen(mi);
             return;
          }
     }

   ll_orig = ll;

   mi = eina_list_data_get(ll);
   if (!eina_list_next(ll))
     ll = mi->menu->items;
   else
     ll = eina_list_next(ll);
   mi = eina_list_data_get(ll);


   while ((!mi->label || strncasecmp(key_compose, mi->label, strlen(key_compose)))
          && ll != ll_orig)
     {
        do
          {
             if (!eina_list_next(ll))
               ll = mi->menu->items;
             else
               ll = eina_list_next(ll);
             mi = eina_list_data_get(ll);
          }
        while (mi->separator);
     }

   e_menu_item_active_set(mi, 1);
   _e_menu_item_ensure_onscreen(mi);
   return;
}
