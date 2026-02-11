_policy_zone_layout_app_dual_custom(E_Border *bd, E_Illume_Config_Zone *cz)
{
   E_Border *app;
   int iy, ny, nh;

   if (!_policy_layout_app_check(bd)) return;

   ZONE_GEOMETRY;

   e_illume_border_indicator_pos_get(bd->zone, NULL, &iy);

   ny = bd->zone->y;
   nh = iy;

   app = e_illume_border_at_xy_get(bd->zone, bd->zone->x, bd->zone->y);
   if ((app) && (bd != app))
     {
	ny = (iy + cz->indicator.size);
	nh = ((bd->zone->y + bd->zone->h) - ny - cz->softkey.size);
     }

   _border_geometry_set(bd, x, ny, w, nh, POL_APP_LAYER);
}
