gpx_waypt_pr(const waypoint* waypointp)
{
  const char* oname;
  char* odesc;
  fs_xml* fs_gpx;
  garmin_fs_t* gmsd;


  odesc = waypointp->notes;
  if (!odesc) {
    odesc = waypointp->description;
  }
  if (!odesc) {
    odesc = waypointp->shortname;
  }

  oname = global_opts.synthesize_shortnames ?
          mkshort(mkshort_handle, odesc) :
          waypointp->shortname;

  gbfprintf(ofd, "<wpt lat=\"" FLT_FMT "\" lon=\"" FLT_FMT "\">\n",
            waypointp->latitude,
            waypointp->longitude);

  gpx_write_common_position(waypointp, "  ");
  gpx_write_common_description(waypointp, "  ", oname);
  gpx_write_common_acc(waypointp, "  ");

  fs_gpx = (fs_xml*)fs_chain_find(waypointp->fs, FS_GPX);
  gmsd = GMSD_FIND(waypointp);
  if (fs_gpx) {
    if (! gmsd) {
      fprint_xml_chain(fs_gpx->tag, waypointp);
    }
  }
  if (gmsd && (gpx_wversion_num > 10)) {

    garmin_fs_xml_fprint(ofd, waypointp);
  }
  gpx_write_common_extensions(waypointp, "  ");
  gbfprintf(ofd, "</wpt>\n");
}
