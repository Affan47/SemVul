print_route_option (const struct route_option *ro, int level)
{
  msg (level, "  route %s/%s/%s/%s",
       show_opt (ro->network),
       show_opt (ro->netmask),
       show_opt (ro->gateway),
       show_opt (ro->metric));
}
