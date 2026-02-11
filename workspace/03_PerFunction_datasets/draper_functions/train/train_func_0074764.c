waypt_add(waypoint *wpt)
{
  double lat_orig = wpt->latitude;
  double lon_orig = wpt->longitude;

  ENQUEUE_TAIL(&waypt_head, &wpt->Q);

  waypt_ct++;

  if (wpt->latitude < -90) {
    wpt->latitude += 180;
  } else if (wpt->latitude > +90) {
    wpt->latitude -= 180;
  }
  if (wpt->longitude < -180) {
    wpt->longitude += 360;
  } else if (wpt->longitude > +180) {
    wpt->longitude -= 360;
  }

  if ((wpt->latitude < -90) || (wpt->latitude > 90.0))
    fatal("%s: Invalid latitude %f in waypoint %s.\n",
          wpt->session->name,
          lat_orig, wpt->shortname ? wpt->shortname : "");
  if ((wpt->longitude < -180) || (wpt->longitude > 180.0))
    fatal("Invalid longitude %f in waypoint %s.\n",
          lon_orig, wpt->shortname ? wpt->shortname : "");
  if (wpt->creation_time < 0) {
    warning("%s: Invalid timestamp in waypoint %s.\n",
            wpt->session->name,
            wpt->shortname ? wpt->shortname : "");
    wpt->creation_time = 0;
  }


  if (wpt->shortname == NULL) {
    if (wpt->description) {
      wpt->shortname = xstrdup(wpt->description);
    } else if (wpt->notes) {
      wpt->shortname = xstrdup(wpt->notes);
    } else {

      char cbuf[10];
      snprintf(cbuf, sizeof(cbuf), "WPT%03d", waypt_ct);
      wpt->shortname = xstrdup(cbuf);
    }
  }

  if (wpt->description == NULL || strlen(wpt->description) == 0) {
    if (wpt->description) {
      xfree(wpt->description);
    }
    if (wpt->notes != NULL) {
      wpt->description = xstrdup(wpt->notes);
    } else  {
      if (wpt->shortname != NULL) {
        wpt->description = xstrdup(wpt->shortname);
      }
    }
  }

  update_common_traits(wpt);

}
