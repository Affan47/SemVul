_map_clicked_double(void *data __UNUSED__, Evas_Object *obj, void *event_info)
{
   printf("clicked,double\n");
   double lon, lat;
   Evas_Event_Mouse_Down *down = event_info;
   if (!down) return;
   if (elm_map_zoom_get(obj) < 5) return;

   elm_map_canvas_to_region_convert(obj, down->canvas.x, down->canvas.y, &lon, &lat);
   printf("x:%d, y:%d, lon:%lf, lat:%lf\n", down->canvas.x, down->canvas.y, lon, lat);

   if (!route_clas)
     {
        route_clas = elm_map_overlay_class_add(obj);
        elm_map_overlay_icon_set(route_clas, _route_icon_get(obj));
        elm_map_overlay_displayed_zoom_min_set(route_clas, 5);
     }

   if (route_start && route_end)
     {
        elm_map_overlay_del(route_start);
        elm_map_overlay_del(route_end);
        elm_map_route_del(route);
        route_start = NULL;
        route_end = NULL;
        route = NULL;
     }

   if (!route_start) route_start = elm_map_overlay_add(obj, lon, lat);
   else route_end = elm_map_overlay_add(obj, lon, lat);

   if (route_start && route_end)
     {
        double start_lon, start_lat, end_lon, end_lat;
        elm_map_overlay_class_append(route_clas, route_start);
        elm_map_overlay_class_append(route_clas, route_end);
        elm_map_overlay_region_get(route_start, &start_lon, &start_lat);
        elm_map_overlay_region_get(route_end, &end_lon, &end_lat);
        route = elm_map_route_add(obj, ELM_MAP_ROUTE_TYPE_MOTOCAR,
                                     ELM_MAP_ROUTE_METHOD_FASTEST,
                                     start_lon, start_lat, end_lon, end_lat,
                                     NULL, NULL);
     }
}
