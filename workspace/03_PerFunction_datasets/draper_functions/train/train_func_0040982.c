_e_drag_win_get(const E_Drop_Handler *h, int xdnd)
{
   Ecore_X_Window hwin = 0;

   if (h->obj)
     {
        switch (h->obj->type)
          {
           case E_GADCON_TYPE:
             if (xdnd) hwin = e_gadcon_xdnd_window_get((E_Gadcon *)(h->obj));
             else hwin = e_gadcon_dnd_window_get((E_Gadcon *)(h->obj));
             break;

           case E_GADCON_CLIENT_TYPE:
             if (xdnd) hwin = e_gadcon_xdnd_window_get(((E_Gadcon_Client *)(h->obj))->gadcon);
             else hwin = e_gadcon_dnd_window_get(((E_Gadcon_Client *)(h->obj))->gadcon);
             break;

           case E_WIN_TYPE:
             hwin = ((E_Win *)(h->obj))->evas_win;
             break;

           case E_ZONE_TYPE:


             hwin = ((E_Zone *)(h->obj))->container->event_win;
             break;

           case E_BORDER_TYPE:
             hwin = ((E_Border *)(h->obj))->event_win;
             break;

           case E_POPUP_TYPE:
             hwin = ((E_Popup *)(h->obj))->evas_win;
             break;


           default:
             break;
          }
     }

   return hwin;
}
