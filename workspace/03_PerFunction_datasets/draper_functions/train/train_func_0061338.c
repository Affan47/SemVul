_e_drag_coords_update(const E_Drop_Handler *h, int *dx, int *dy)
{
   int px = 0, py = 0;

   *dx = 0;
   *dy = 0;
   if (h->obj)
     {
        switch (h->obj->type)
          {
           E_Gadcon *gc;
           case E_GADCON_TYPE:
             gc = (E_Gadcon*)h->obj;
             e_gadcon_canvas_zone_geometry_get(gc, &px, &py, NULL, NULL);
             if (!gc->toolbar) break;
             px += gc->toolbar->fwin->x;
             py += gc->toolbar->fwin->y;
             break;

           case E_GADCON_CLIENT_TYPE:
             gc = ((E_Gadcon_Client *)(h->obj))->gadcon;
             e_gadcon_canvas_zone_geometry_get(gc, &px, &py, NULL, NULL);
             if (!gc->toolbar) break;
             px += gc->toolbar->fwin->x;
             py += gc->toolbar->fwin->y;
             break;

           case E_WIN_TYPE:
             px = ((E_Win *)(h->obj))->x;
             py = ((E_Win *)(h->obj))->y;
             break;

           case E_ZONE_TYPE:


             break;

           case E_BORDER_TYPE:
             px = ((E_Border *)(h->obj))->x + ((E_Border *)(h->obj))->fx.x;
             py = ((E_Border *)(h->obj))->y + ((E_Border *)(h->obj))->fx.y;
             break;

           case E_POPUP_TYPE:
             px = ((E_Popup *)(h->obj))->x;
             py = ((E_Popup *)(h->obj))->y;
             break;


           default:
             break;
          }
     }
   *dx += px;
   *dy += py;
}
