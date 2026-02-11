_e_manager_cb_window_configure(void *data, int ev_type __UNUSED__, void *ev)
{
   E_Manager *man;
   Ecore_X_Event_Window_Configure *e;

   man = data;
   e = ev;
   if (e->win != man->root) return ECORE_CALLBACK_PASS_ON;
   e_manager_resize(man, e->w, e->h);
   return ECORE_CALLBACK_PASS_ON;
}
