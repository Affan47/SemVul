position_process_route(const route_head * rh)
{
  int i = rh->rte_waypt_ct;

  if (i) {
    cur_rte = (route_head *)rh;
    position_runqueue((queue *)&rh->waypoint_list, i, rtedata);
    cur_rte = NULL;
  }

}
