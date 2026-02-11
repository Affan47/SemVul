_e_pointer_cb_idle_poller(void *data)
{
   E_Pointer *p;
   int x, y;

   if (!(p = data)) return ECORE_CALLBACK_RENEW;
   if ((e_powersave_mode_get() >= E_POWERSAVE_MODE_MEDIUM) ||
       (!e_config->idle_cursor))
     {
        p->idle_poller = NULL;
        return ECORE_CALLBACK_CANCEL;
     }


   ecore_x_pointer_xy_get(p->win, &x, &y);
   if ((x != p->x) || (y != p->y))
     {


          p->x = x;
          p->y = y;
          if (p->idle)
            {
               if (p->pointer_object)
                 edje_object_signal_emit(p->pointer_object,
                                         "e,state,mouse,active", "e");
               p->idle = 0;
            }

          return ECORE_CALLBACK_RENEW;
     }

   if (!p->idle)
     {
        if (p->pointer_object)
          edje_object_signal_emit(p->pointer_object, "e,state,mouse,idle", "e");
        p->idle = 1;
     }
   return ECORE_CALLBACK_RENEW;
}
