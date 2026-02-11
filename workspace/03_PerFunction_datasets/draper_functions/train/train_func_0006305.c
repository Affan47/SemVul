gpx_route_disp(const waypoint* waypointp)
{
  fs_xml* fs_gpx;

  gbfprintf(ofd, "  <rtept lat=\"" FLT_FMT_R "\" lon=\"" FLT_FMT_R "\">\n",
            waypointp->latitude,
            waypointp->longitude);

  gpx_write_common_position(waypointp, "    ");
  gpx_write_common_description(waypointp, "    ", waypointp->shortname);
  gpx_write_common_acc(waypointp, "    ");

  fs_gpx = (fs_xml*)fs_chain_find(waypointp->fs, FS_GPX);
  if (fs_gpx) {
    fprint_xml_chain(fs_gpx->tag, waypointp);
  }

  gpx_write_common_extensions(waypointp, "    ");
  gbfprintf(ofd, "  </rtept>\n");
}
