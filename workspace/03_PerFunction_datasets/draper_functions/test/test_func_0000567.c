_on_mouse_up(void *data,
             Evas *e __UNUSED__,
             Evas_Object *obj __UNUSED__,
             void *event_info)
{
   Elm_Segment_Item *it;
   Evas_Event_Mouse_Up *ev;
   Evas_Coord x, y, w, h;

   it = data;
   ELM_SEGMENT_CONTROL_DATA_GET(WIDGET(it), sd);

   if (elm_widget_disabled_get(ELM_WIDGET_DATA(sd)->obj)) return;

   if (it == sd->selected_item) return;

   ev = event_info;
   evas_object_geometry_get(VIEW(it), &x, &y, &w, &h);

   if ((ev->canvas.x >= x) && (ev->output.x <= (x + w)) && (ev->canvas.y >= y)
       && (ev->canvas.y <= (y + h)))
     _segment_on(it);
   else
     edje_object_signal_emit(VIEW(it), "elm,state,segment,normal", "elm");
}
