_spacer_down_cb(void *data,
                Evas *e __UNUSED__,
                Evas_Object *obj __UNUSED__,
                void *event_info)
{
   ELM_SLIDER_DATA_GET(data, sd);

   Evas_Event_Mouse_Down *ev = event_info;
   Evas_Coord x, y, w, h;
   double button_x = 0.0, button_y = 0.0;

   sd->spacer_down = EINA_TRUE;
   sd->val2 = sd->val;
   evas_object_geometry_get(sd->spacer, &x, &y, &w, &h);
   sd->downx = ev->canvas.x - x;
   sd->downy = ev->canvas.y - y;
   if (sd->horizontal)
     {
        button_x = ((double)ev->canvas.x - (double)x) / (double)w;
        if (button_x > 1) button_x = 1;
        if (button_x < 0) button_x = 0;
     }
   else
     {
        button_y = ((double)ev->canvas.y - (double)y) / (double)h;
        if (button_y > 1) button_y = 1;
        if (button_y < 0) button_y = 0;
     }

   edje_object_part_drag_value_set
     (ELM_WIDGET_DATA(sd)->resize_obj, "elm.dragable.slider",
     button_x, button_y);
   _slider_update(data);
   evas_object_smart_callback_call(data, SIG_DRAG_START, NULL);
   elm_layout_signal_emit(data, "elm,state,indicator,show", "elm");
}
