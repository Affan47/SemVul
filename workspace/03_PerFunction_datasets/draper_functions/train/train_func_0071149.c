on_left(void *data, Evas_Object *o __UNUSED__, const char *em __UNUSED__, const char *src __UNUSED__)
{
   Evas_Object *mover;
   static int ox, oy, ow, oh;
   int mx, my;
   int action = (int)(long)data;
   E_Gadcon_Client *drag_gcc;
   int layer = Man->visible;

   drag_gcc = Man->drag_gcc[layer];

   mover = _get_mover(drag_gcc);
   if (action == DRAG_START)
     {
        drag_gcc->resizing = 1;
        evas_pointer_output_xy_get(drag_gcc->gadcon->evas, &mx, &my);
        evas_object_geometry_get(mover, &ox, &oy, &ow, &oh);
        drag_gcc->dx = mx - ox;
     }
   else if (action == DRAG_STOP)
     {
        drag_gcc->resizing = 0;
        drag_gcc->dx = 0;
        _save_widget_position(drag_gcc);
     }
   else if ((action == DRAG_MOVE) && drag_gcc->resizing)
     {
        int w;

        evas_pointer_output_xy_get(drag_gcc->gadcon->evas, &mx, &my);

        w = ox + ow + drag_gcc->dx - mx;

        if (w < drag_gcc->min.w)
          {
             mx -= drag_gcc->min.w - w;
             w = drag_gcc->min.w;
          }

        if (mx < drag_gcc->dx)
          {
             w += mx - drag_gcc->dx;
             mx = drag_gcc->dx;
          }

        evas_object_resize(mover, w, oh);
        evas_object_move(mover, mx - drag_gcc->dx, oy);

        evas_object_resize(drag_gcc->o_frame, w, oh);
        evas_object_move(drag_gcc->o_frame, mx - drag_gcc->dx, oy);
     }
}
