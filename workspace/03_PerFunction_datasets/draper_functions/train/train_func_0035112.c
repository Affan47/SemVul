e_menu_item_icon_edje_set(E_Menu_Item *mi, const char *icon, const char *key)
{
   E_OBJECT_CHECK(mi);
   E_OBJECT_TYPE_CHECK(mi, E_MENU_ITEM_TYPE);
   if (((mi->icon) && (icon) && (!strcmp(icon, mi->icon))) ||
       ((!mi->icon) && (!icon)) ||
       ((key) && (mi->icon_key) && (!strcmp(key, mi->icon_key))))
     return;
   eina_stringshare_replace(&mi->icon, icon);
   eina_stringshare_replace(&mi->icon_key, key);
   mi->changed = 1;
   mi->menu->changed = 1;
}
