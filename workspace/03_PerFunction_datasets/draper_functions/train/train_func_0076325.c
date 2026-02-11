gtc_trk_pnt_e(const char* args, const char** unused)
{
  if (wpt_tmp->longitude != 0. && wpt_tmp->latitude != 0.) {
    if (lap_s) {


      char cbuf[10];
      waypoint* wpt_lap_s = waypt_dupe(wpt_tmp);
      snprintf(cbuf, sizeof(cbuf), "LAP%03d", lap_ct);
      wpt_lap_s->shortname = xstrdup(cbuf);
      waypt_add(wpt_lap_s);
    }

    track_add_wpt(trk_head, wpt_tmp);
  } else {
    waypt_free(wpt_tmp);
  }

  wpt_tmp = NULL;
  lap_s = 0;
}
