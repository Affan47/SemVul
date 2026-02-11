_ecore_evas_x_event_window_configure(void *data __UNUSED__, int type __UNUSED__, void *event)
{
   Ecore_Evas *ee;
   Ecore_X_Event_Window_Configure *e;

   e = event;
   ee = ecore_event_window_match(e->win);
   if (!ee) return ECORE_CALLBACK_PASS_ON;
   if (e->win != ee->prop.window) return ECORE_CALLBACK_PASS_ON;
   if (ee->engine.x.direct_resize) return ECORE_CALLBACK_PASS_ON;

   ee->engine.x.configure_coming = 0;
   if ((e->from_wm) || (ee->prop.override))
     {
        if ((ee->x != e->x) || (ee->y != e->y))
          {
             ee->x = e->x;
             ee->y = e->y;
             ee->req.x = ee->x;
             ee->req.y = ee->y;
             if (ee->func.fn_move) ee->func.fn_move(ee);
          }
     }
   if ((ee->w != e->w) || (ee->h != e->h))
     {
        ee->w = e->w;
        ee->h = e->h;
        ee->req.w = ee->w;
        ee->req.h = ee->h;
        if ((ee->rotation == 90) || (ee->rotation == 270))
          {
             evas_output_size_set(ee->evas, ee->h, ee->w);
             evas_output_viewport_set(ee->evas, 0, 0, ee->h, ee->w);
          }
        else
          {
             evas_output_size_set(ee->evas, ee->w, ee->h);
             evas_output_viewport_set(ee->evas, 0, 0, ee->w, ee->h);
          }
        if (ee->prop.avoid_damage)
          {
             int pdam;

             pdam = ecore_evas_avoid_damage_get(ee);
             ecore_evas_avoid_damage_set(ee, 0);
             ecore_evas_avoid_damage_set(ee, pdam);
          }
        if ((ee->shaped) || (ee->alpha))
          _ecore_evas_x_resize_shape(ee);
        if ((ee->expecting_resize.w > 0) && (ee->expecting_resize.h > 0))
          {
             if ((ee->expecting_resize.w == ee->w) &&
                 (ee->expecting_resize.h == ee->h))
               _ecore_evas_mouse_move_process(ee, ee->mouse.x, ee->mouse.y,
                                              ecore_x_current_time_get());
             ee->expecting_resize.w = 0;
             ee->expecting_resize.h = 0;
          }
        if (ee->func.fn_resize) ee->func.fn_resize(ee);
     }
   return ECORE_CALLBACK_PASS_ON;
}
