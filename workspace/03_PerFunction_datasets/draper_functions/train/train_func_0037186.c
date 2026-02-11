_bd_hook(void *d __UNUSED__, E_Border *bd)
{
   E_Menu_Item *mi;
   E_Menu *m;
   Eina_List *l;
   if (!bd->border_menu) return;
   m = bd->border_menu;


   EINA_LIST_FOREACH(m->items, l, mi)
     if (mi->separator) break;
   if ((!mi) || (!mi->separator)) return;
   l = eina_list_prev(l);
   mi = eina_list_data_get(l);
   if (!mi) return;

   mi = e_menu_item_new_relative(m, mi);
   e_menu_item_label_set(mi, _("Take Shot"));
   e_util_menu_item_theme_icon_set(mi, "screenshot");
   e_menu_item_callback_set(mi, _e_mod_menu_border_cb, bd);
}
