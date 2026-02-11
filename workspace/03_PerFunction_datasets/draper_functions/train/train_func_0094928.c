_il_home_cb_border_add(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   E_Event_Border_Add *ev;
   Il_Home_Exec *exe;
   Eina_List *l;

   ev = event;
   EINA_LIST_FOREACH(exes, l, exe)
     {
        if (!exe->border)
          {
             if ((exe->startup_id == ev->border->client.netwm.startup_id) ||
                 (exe->pid == ev->border->client.netwm.pid))
               {
                  exe->border = ev->border;
               }
          }
        if (!exe->border) continue;
        if (exe->border->zone != exe->zone)
          {
             exe->border->zone = exe->zone;
             exe->border->x = exe->zone->x;
             exe->border->y = exe->zone->y;
             exe->border->changes.pos = 1;
             exe->border->changed = 1;
          }
        if (exe->handle)
          {
             e_busycover_pop(exe->cover, exe->handle);
             exe->handle = NULL;
          }
        if (exe->timeout) ecore_timer_del(exe->timeout);
        exe->timeout = NULL;
     }
   return ECORE_CALLBACK_PASS_ON;
}
