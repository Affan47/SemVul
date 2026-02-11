router_get_advertised_bandwidth_capped(const routerinfo_t *router)
{
  uint32_t result = router->bandwidthcapacity;
  if (result > router->bandwidthrate)
    result = router->bandwidthrate;
  if (result > DEFAULT_MAX_BELIEVABLE_BANDWIDTH)
    result = DEFAULT_MAX_BELIEVABLE_BANDWIDTH;
  return result;
}
