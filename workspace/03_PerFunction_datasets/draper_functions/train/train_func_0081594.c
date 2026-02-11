e_zone_edge_free(E_Zone_Edge edge)
{
   Eina_List *l, *ll, *lll;
   E_Manager *man;
   E_Container *con;
   E_Zone *zone;

   EINA_LIST_FOREACH(e_manager_list(), l, man)
     {
        EINA_LIST_FOREACH(man->containers, ll, con)
          {
             EINA_LIST_FOREACH(con->zones, lll, zone)
               {
                  switch (edge)
                    {
                     case E_ZONE_EDGE_NONE:

                       break;

                     case E_ZONE_EDGE_LEFT:
                       if (zone->edge.left) ecore_x_window_free(zone->edge.left);
                       zone->edge.left = 0;
                       break;

                     case E_ZONE_EDGE_RIGHT:
                       if (zone->edge.right) ecore_x_window_free(zone->edge.right);
                       zone->edge.right = 0;
                       break;

                     case E_ZONE_EDGE_TOP:
                       if (zone->edge.top) ecore_x_window_free(zone->edge.top);
                       zone->edge.top = 0;
                       break;

                     case E_ZONE_EDGE_BOTTOM:
                       if (zone->edge.bottom) ecore_x_window_free(zone->edge.bottom);
                       zone->edge.bottom = 0;
                       break;

                     case E_ZONE_EDGE_TOP_LEFT:
                       if (zone->corner.left_top) ecore_x_window_free(zone->corner.left_top);
                       if (zone->corner.top_left) ecore_x_window_free(zone->corner.top_left);
                       zone->corner.left_top = 0;
                       zone->corner.top_left = 0;
                       break;

                     case E_ZONE_EDGE_TOP_RIGHT:
                       if (zone->corner.top_right) ecore_x_window_free(zone->corner.top_right);
                       if (zone->corner.right_top) ecore_x_window_free(zone->corner.right_top);
                       zone->corner.top_right = 0;
                       zone->corner.right_top = 0;
                       break;

                     case E_ZONE_EDGE_BOTTOM_RIGHT:
                       if (zone->corner.right_bottom) ecore_x_window_free(zone->corner.right_bottom);
                       if (zone->corner.bottom_right) ecore_x_window_free(zone->corner.bottom_right);
                       zone->corner.right_bottom = 0;
                       zone->corner.bottom_right = 0;
                       break;

                     case E_ZONE_EDGE_BOTTOM_LEFT:
                       if (zone->corner.bottom_left) ecore_x_window_free(zone->corner.bottom_left);
                       if (zone->corner.left_bottom) ecore_x_window_free(zone->corner.left_bottom);
                       zone->corner.bottom_left = 0;
                       zone->corner.left_bottom = 0;
                       break;
                    }
               }
          }
     }
}
