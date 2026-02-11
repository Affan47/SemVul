any_route_add_wpt(route_head *rte, waypoint *wpt, int *ct, int synth)
{
  ENQUEUE_TAIL(&rte->waypoint_list, &wpt->Q);
  rte->rte_waypt_ct++;
  if (ct) {
    (*ct)++;
  }
  if (synth && !wpt->shortname) {
    char tmpnam[10];
    snprintf(tmpnam, sizeof(tmpnam), "RPT%03d",*ct);
    wpt->shortname = xstrdup(tmpnam);
    wpt->wpt_flags.shortname_is_synthetic = 1;
  }
  update_common_traits(wpt);
}
