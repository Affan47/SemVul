routerlist_descriptors_added(smartlist_t *sl, int from_cache)
{
  tor_assert(sl);
  control_event_descriptors_changed(sl);
  SMARTLIST_FOREACH_BEGIN(sl, routerinfo_t *, ri) {
    if (ri->purpose == ROUTER_PURPOSE_BRIDGE)
      learned_bridge_descriptor(ri, from_cache);
    if (ri->needs_retest_if_added) {
      ri->needs_retest_if_added = 0;
      dirserv_single_reachability_test(approx_time(), ri);
    }
  } SMARTLIST_FOREACH_END(ri);
}
