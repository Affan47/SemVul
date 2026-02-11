skyforce_read(void)
{
  char *str;
  route_head *rte, *trk;

  wpt_num = 0;
  rte = trk = NULL;
  rte_num = -1;

  while ((str = gbfgetstr(fin))) {

    waypoint *wpt;
    int i;

    str = lrtrim(str);
    if (*str == '\0') {
      continue;
    }

    switch (*str) {

    case 'W':
      wpt = skyforce_parse_wpt(str, NULL);
      if (wpt == NULL) {
        continue;
      }
      waypt_add(wpt);
      break;

    case 'R':
      wpt = skyforce_parse_wpt(str, &i);
      if (wpt == NULL) {
        continue;
      }

      if (i != rte_num) {
        rte_num = i;
        rte = NULL;
      }

      if (rte == NULL) {
        rte = route_head_alloc();
        route_add_head(rte);
        rte->rte_num = rte_num;
      }
      route_add_wpt(rte, wpt);
      break;

    case 'L':
      wpt = skyforce_parse_trk(str);
      if (wpt == NULL) {
        continue;
      }
      if (trk == NULL) {
        trk = route_head_alloc();
        track_add_head(trk);
      }
      track_add_wpt(trk, wpt);
      break;

    default:
      fatal(MYNAME ": Invalid line marker '%c'!\n", *str);
    }
  }
}
