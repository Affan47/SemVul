_e_menu_active_call(void)
{
   E_Menu_Item *mi;

   mi = _e_menu_item_active_get();
   if (mi)
     {
        if (mi->check)
          e_menu_item_toggle_set(mi, !mi->toggle);
        if ((mi->radio) && (!e_menu_item_toggle_get(mi)))
          e_menu_item_toggle_set(mi, 1);
        if (mi->cb.func)
          mi->cb.func(mi->cb.data, mi->menu, mi);
        return 1;
     }
   return -1;
}
