e_menu_root_get(E_Menu *m)
{
   E_Menu *ret;

   E_OBJECT_CHECK_RETURN(m, NULL);
   E_OBJECT_TYPE_CHECK_RETURN(m, E_MENU_TYPE, NULL);
   ret = m;
   while ((ret->parent_item) && (ret->parent_item->menu))
     ret = ret->parent_item->menu;

   return ret;
}
