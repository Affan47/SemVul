_map_route_loaded(void *data __UNUSED__, Evas_Object *obj, void *event_info __UNUSED__)
{
   printf("route,loaded\n");
   double d;
   const char *w, *n;

   d = elm_map_route_distance_get(route);
   printf("route distance = %lf km\n", d);

   w = elm_map_route_waypoint_get(route);
   if (w) printf("[waypoints]\n%s\n", w);

   n = elm_map_route_node_get(route);
   if (n) printf("[nodes]\n%s\n", n);

   if (route_ovl) elm_map_overlay_del(route_ovl);
   route_ovl = elm_map_overlay_route_add(obj, route);
}
