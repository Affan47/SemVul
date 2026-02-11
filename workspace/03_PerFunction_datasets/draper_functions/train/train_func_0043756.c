gpx_write_bounds(void)
{
  waypt_init_bounds(&all_bounds);

  waypt_disp_all(gpx_waypt_bound_calc);
  route_disp_all(NULL, NULL, gpx_waypt_bound_calc);
  track_disp_all(NULL, NULL, gpx_waypt_bound_calc);

  if (waypt_bounds_valid(&all_bounds)) {
    gbfprintf(ofd, "<bounds minlat=\"%0.9f\" minlon=\"%0.9f\" "
              "maxlat=\"%0.9f\" maxlon=\"%0.9f\"/>\n",
              all_bounds.min_lat, all_bounds.min_lon,
              all_bounds.max_lat, all_bounds.max_lon);
  }
}
