elm_transit_paused_set(Elm_Transit *transit, Eina_Bool paused)
{
   ELM_TRANSIT_CHECK_OR_RETURN(transit);

   if (!transit->animator) return;

   if (paused)
     {
        if (transit->time.paused > 0)
          return;
        ecore_animator_freeze(transit->animator);
        transit->time.paused = ecore_loop_time_get();
     }
   else
     {
        if (transit->time.paused == 0)
          return;
        ecore_animator_thaw(transit->animator);
        transit->time.delayed += (ecore_loop_time_get() - transit->time.paused);
        transit->time.paused = 0;
     }
}
