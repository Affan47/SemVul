_e_smart_monitor_frame_cb_rotate_stop(void *data, Evas_Object *obj EINA_UNUSED, const char *emission EINA_UNUSED, const char *source EINA_UNUSED)
{
   Evas_Object *mon;
   E_Smart_Data *sd;
   Ecore_X_Randr_Orientation orient;
   Evas_Coord nx = 0, ny = 0;
   Evas_Coord nw = 0, nh = 0;
   int rot = 0;


   if (!(mon = data)) return;
   if (!(sd = evas_object_smart_data_get(mon))) return;


   sd->rotating = EINA_FALSE;

   sd->current.rotation += sd->orig.rotation;


   orient = _e_smart_monitor_orientation_get(sd->current.rotation);


   if (sd->current.orientation == orient) return;


   e_layout_child_geometry_get(mon, &nx, &ny, &nw, &nh);


   rot = _e_smart_monitor_rotation_get(orient);
   if (rot != sd->current.rotation)
     {

        sd->current.rotation = rot;
     }


   if ((orient == ECORE_X_RANDR_ORIENTATION_ROT_90) ||
       (orient == ECORE_X_RANDR_ORIENTATION_ROT_270))
     {
        if ((sd->current.orientation != ECORE_X_RANDR_ORIENTATION_ROT_90) ||
            (sd->current.orientation != ECORE_X_RANDR_ORIENTATION_ROT_270))
          {
             int sx = 0, sy = 0;


             e_layout_child_resize(mon, nh, nw);


             _e_smart_monitor_resolution_set(sd, sd->current.mode->height,
                                            sd->current.mode->width);


             sx = ((nw - nh) / 2);
             sy = ((nh - nw) / 2);


             nx -= (sx + sd->layout.x);
             ny -= (sy - sd->layout.y);


             e_layout_child_move(mon, nx, ny);
          }
     }
   else if ((orient == ECORE_X_RANDR_ORIENTATION_ROT_0) ||
            (orient == ECORE_X_RANDR_ORIENTATION_ROT_180))
     {
        if ((sd->current.orientation != ECORE_X_RANDR_ORIENTATION_ROT_0) ||
            (sd->current.orientation != ECORE_X_RANDR_ORIENTATION_ROT_180))
          {

             e_layout_child_resize(mon, nh, nw);


             _e_smart_monitor_resolution_set(sd, sd->current.mode->width,
                                            sd->current.mode->height);


             e_layout_child_move(mon, sd->current.x, sd->current.y);
          }
     }


   if (sd->orig.orientation != orient)
     sd->changes |= E_SMART_MONITOR_CHANGED_ROTATION;
   else
     sd->changes &= ~(E_SMART_MONITOR_CHANGED_ROTATION);


   evas_object_smart_callback_call(mon, "monitor_rotated", NULL);


   _e_smart_monitor_map_remove(sd, orient);


   sd->current.orientation = orient;
}
