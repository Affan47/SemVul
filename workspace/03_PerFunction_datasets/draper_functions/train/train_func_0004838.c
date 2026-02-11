_e_main_cb_idle_before(void *data __UNUSED__)
{
   Eina_List *l, *pl;
   E_Before_Idler *eb;

   e_menu_idler_before();
   e_focus_idler_before();
   e_border_idler_before();
   e_popup_idler_before();
   e_drag_idler_before();
   e_pointer_idler_before();
   EINA_LIST_FOREACH(_idle_before_list, l, eb)
     {
        if (!eb->delete_me)
          {
             if (!eb->func(eb->data)) eb->delete_me = 1;
          }
     }
   EINA_LIST_FOREACH_SAFE (_idle_before_list, pl, l, eb)
     {
        if ((eb->once) || (eb->delete_me))
          {
             _idle_before_list =
               eina_list_remove_list(_idle_before_list, pl);
             free(eb);
          }
     }
   edje_thaw();
   return ECORE_CALLBACK_RENEW;
}
