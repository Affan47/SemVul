_ecore_evas_x_resize(Ecore_Evas *ee, int w, int h)
{
   ee->req.w = w;
   ee->req.h = h;
   if (ee->engine.x.direct_resize)
     {
        if ((ee->w != w) || (ee->h != h))
          {
             ee->w = w;
             ee->h = h;
             ecore_x_window_resize(ee->prop.window, w, h);
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
             if (ee->func.fn_resize) ee->func.fn_resize(ee);
          }
     }
   else if (((ee->w != w) || (ee->h != h)) ||
            (ee->engine.x.configure_coming))
     {
        ee->engine.x.configure_coming = 1;
        ecore_x_window_resize(ee->prop.window, w, h);
     }
}
