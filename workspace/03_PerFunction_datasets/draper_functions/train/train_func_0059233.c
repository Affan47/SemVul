osm_node(const char* args, const char** attrv)
{
  const char** avp = &attrv[0];

  wpt = waypt_new();

  while (*avp) {
    if (strcmp(avp[0], "id") == 0) {
      xasprintf(&wpt->description, "osm-id %s", avp[1]);
      if (! avltree_insert(waypoints, avp[1], (void*)wpt)) {
        warning(MYNAME ": Duplicate osm-id %s!\n", avp[1]);
      } else {
        wpt->wpt_flags.fmt_use = 1;
      }
    } else if (strcmp(avp[0], "user") == 0) ;
    else if (strcmp(avp[0], "lat") == 0) {
      wpt->latitude = atof(avp[1]);
    } else if (strcmp(avp[0], "lon") == 0) {
      wpt->longitude = atof(avp[1]);
    } else if (strcmp(avp[0], "timestamp") == 0) {
      wpt->creation_time = xml_parse_time(avp[1], &wpt->microseconds);
    }

    avp += 2;
  }
}
