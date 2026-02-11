_ecore_evas_x_move(Ecore_Evas *ee, int x, int y)
{
   ee->req.x = x;
   ee->req.y = y;
   if (ee->engine.x.direct_resize)
     {
        if (!ee->engine.x.managed)
          {
             if ((x != ee->x) || (y != ee->y))
               {
                  ee->x = x;
                  ee->y = y;
                  ecore_x_window_move(ee->prop.window, x, y);
                  if (!ee->should_be_visible)
                    {

                       ee->prop.request_pos = 1;
                       _ecore_evas_x_size_pos_hints_update(ee);
                    }
                  if (ee->func.fn_move) ee->func.fn_move(ee);
               }
          }
     }
   else
     {
        if (((ee->x != x) || (ee->y != y)) ||
            (ee->engine.x.configure_coming))
          {
             ee->engine.x.configure_coming = 1;
             if (!ee->engine.x.managed)
               {
                  ee->x = x;
                  ee->y = y;
               }
             ecore_x_window_move(ee->prop.window, x, y);
          }
        if (!ee->should_be_visible)
          {

             ee->prop.request_pos = 1;
             _ecore_evas_x_size_pos_hints_update(ee);
          }
     }
}
