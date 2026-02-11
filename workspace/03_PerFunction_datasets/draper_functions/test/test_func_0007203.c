_e_desk_show_animator(void *data)
{
   E_Desk *desk;
   E_Border_List *bl;
   E_Border *bd;
   double t, dt, spd;

   desk = data;

   if (!desk->animating)
     {
        _e_desk_show_end(desk);
        desk->animator = NULL;
        return ECORE_CALLBACK_CANCEL;
     }

   t = ecore_loop_time_get();
   dt = -1.0;
   spd = e_config->desk_flip_animate_time;
   bl = e_container_border_list_first(desk->zone->container);
   while ((bd = e_container_border_list_next(bl)))
     {
        if ((bd->desk->zone == desk->zone) && (!bd->iconic))
          {
             if (bd->moving)
               {
               }
             else if ((bd->desk == desk) && (!bd->sticky))
               {
                  if (!bd->visible)
                    e_border_show(bd);

                  dt = (t - bd->fx.start.t) / spd;
                  if (dt > 1.0) dt = 1.0;
                  dt = 1.0 - dt;
                  dt *= dt;
                  e_border_fx_offset(bd,
                                     ((double)bd->fx.start.x * dt),
                                     ((double)bd->fx.start.y * dt));
               }
          }
     }
   e_container_border_list_free(bl);
   if (dt <= 0.0)
     desk->animating = EINA_FALSE;

   return ECORE_CALLBACK_RENEW;
}
