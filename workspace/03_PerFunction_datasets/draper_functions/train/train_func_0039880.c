wpr_read(void)
{
  struct wprdata wprdata;
  struct rtehdr* rtehdr;
  struct rte* rte;
  int i, j, idx;
  waypoint* WP;
  route_head* RT;

  if (gbfread(&wprdata, sizeof(struct wprdata), 1, fin) != 1) {
    fatal(MYNAME ": Read error on %s\n", fin->name);
  }
  wpr_swap(&wprdata);
  if (wprdata.wpthdr.id != WPT_HDR_ID ||
      wprdata.rtehdr.id != RTE_HDR_ID) {
    fatal(MYNAME ": %s is not in Alan .wpr format.\n", fin->name);
  }


  for (i=0; i<MAXWPT; i++) {
    WP = get_wpt(&wprdata, i);
    if (WP != NULL) {
      waypt_add(WP);
    }
  }


  rtehdr = &(wprdata.rtehdr);
  for (i=0; i<MAXRTE; i++) {
    idx = rtehdr->idx[i];
    if (idx == RTE_IDX_NONE || rtehdr->used[idx] == RTE_UNUSED) {
      continue;
    }
    rte = &(wprdata.rte[idx]);

    RT = route_head_alloc();
    RT->rte_num = i;
    for (j=RTE_NAME_LEN-1; j >= 0 && rte->name[j] == ' '; j--) {};
    RT->rte_name = xstrndup(rte->name,j+1);
    for (j=RTE_COMMENT_LEN-1; j >= 0 && rte->comment[j] == ' '; j--) {};
    if (j >= 0) {
      RT->rte_desc = xstrndup(rte->comment,j+1);
    } else {
      RT->rte_desc = xstrdup("");
    }

    route_add_head(RT);


    for (j=0; j<rte->wptnum; j++) {
      WP = get_wpt(&wprdata, rte->wptidx[j]);
      if (WP != NULL) {
        route_add_wpt(RT, WP);
      }
    }
  }
}
