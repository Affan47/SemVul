garmin_txt_write(void)
{
  char* grid_str, *c;
  const char* datum_str;

  grid_str = xstrdup(gt_get_mps_grid_longname(grid_index, MYNAME));
  while ((c = strchr(grid_str, '*'))) {
    *c = 0xB0;
  }
  cet_gbfprintf(fout, &cet_cs_vec_cp1252, "Grid\t%s\r\n", grid_str);
  xfree(grid_str);

  datum_str = gt_get_mps_datum_name(datum_index);
  gbfprintf(fout, "Datum\t%s\r\n\r\n", datum_str);

  waypoints = 0;
  gtxt_flags.enum_waypoints = 1;
  waypt_disp_all(enum_waypt_cb);
  route_disp_all(NULL, NULL, enum_waypt_cb);
  gtxt_flags.enum_waypoints = 0;

  if (waypoints > 0) {
    int i;

    wpt_a_ct = 0;
    wpt_a = (waypoint**)xcalloc(waypoints, sizeof(*wpt_a));
    waypt_disp_all(enum_waypt_cb);
    route_disp_all(NULL, NULL, enum_waypt_cb);
    qsort(wpt_a, waypoints, sizeof(*wpt_a), sort_waypt_cb);

    gbfprintf(fout, "Header\t%s\r\n\r\n", headers[waypt_header]);
    for (i = 0; i < waypoints; i++) {
      waypoint* wpt = wpt_a[i];
      write_waypt(wpt);
    }
    xfree(wpt_a);

    route_idx = 0;
    route_info = (info_t*) xcalloc(route_count(), sizeof(struct info_s));
    routepoints = 0;
    route_disp_all(prework_hdr_cb, prework_tlr_cb, prework_wpt_cb);
    if (routepoints > 0) {
      route_idx = 0;
      route_disp_all(route_disp_hdr_cb, route_disp_tlr_cb, route_disp_wpt_cb);
    }
    xfree(route_info);
  }

  route_idx = 0;
  route_info = (info_t*) xcalloc(track_count(), sizeof(struct info_s));
  routepoints = 0;
  track_disp_all(prework_hdr_cb, prework_tlr_cb, prework_wpt_cb);

  if (routepoints > 0) {
    route_idx = 0;
    track_disp_all(track_disp_hdr_cb, track_disp_tlr_cb, track_disp_wpt_cb);
  }
  xfree(route_info);
}
