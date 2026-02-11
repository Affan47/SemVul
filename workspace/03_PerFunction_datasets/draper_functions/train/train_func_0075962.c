_e_shelf_module_init_end_handler_cb(void *data __UNUSED__, int type __UNUSED__, void *event __UNUSED__)
{
   Eina_List *l;
   E_Shelf *es;

   EINA_LIST_FOREACH(shelves, l, es)
     {
        if ((!es->gadcon->populate_requests) || (!es->gadcon->cf->clients))
          {
             if (e_shelf_desk_visible(es, NULL))
               e_shelf_show(es);
          }
        else if (!es->module_init_end_timer)
          es->module_init_end_timer = ecore_timer_add(3.0, _e_shelf_module_init_end_timer_cb, es);
     }
   return ECORE_CALLBACK_RENEW;
}
