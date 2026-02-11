_e_border_cb_window_stack_request(void *data  __UNUSED__,
                                  int ev_type __UNUSED__,
                                  void *ev)
{
   E_Border *bd;
   Ecore_X_Event_Window_Stack_Request *e;

   e = ev;
   bd = e_border_find_by_client_window(e->win);
   if (!bd)
     {
        if (e_stolen_win_get(e->win)) return ECORE_CALLBACK_PASS_ON;
        if (!e_util_container_window_find(e->win))
          {
             if (e->detail == ECORE_X_WINDOW_STACK_ABOVE)
               ecore_x_window_raise(e->win);
             else if (e->detail == ECORE_X_WINDOW_STACK_BELOW)
               ecore_x_window_lower(e->win);
          }
        return ECORE_CALLBACK_PASS_ON;
     }
   if (e->detail == ECORE_X_WINDOW_STACK_ABOVE)
     e_border_raise(bd);
   else if (e->detail == ECORE_X_WINDOW_STACK_BELOW)
     e_border_lower(bd);
   return ECORE_CALLBACK_PASS_ON;
}
