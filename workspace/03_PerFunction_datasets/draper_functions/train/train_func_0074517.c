_e_pointer_cb_mouse_down(void *data __UNUSED__,
                         int   type __UNUSED__,
                         void *event __UNUSED__)
{
   Eina_List *l;
   E_Pointer *p;

   EINA_LIST_FOREACH(_e_pointers, l, p)
     {
        _e_pointer_active_handle(p);
        if (e_powersave_mode_get() < E_POWERSAVE_MODE_EXTREME)
          {
             if (p->pointer_object)
               edje_object_signal_emit(p->pointer_object,
                                       "e,action,mouse,down", "e");
          }
     }
   return ECORE_CALLBACK_PASS_ON;
}
