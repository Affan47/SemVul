goog_segment(const char* args, const char** unused)
{
  waypoint* wpt_tmp;

  wpt_tmp = route_find_waypt_by_name(routehead[goog_segroute], goog_segname);
  if (wpt_tmp) {
    xfree(wpt_tmp->shortname);
    wpt_tmp->shortname = mkshort(desc_handle,args);
    wpt_tmp->description = xstrdup(args);
  }
}
