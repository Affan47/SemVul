dumpChanG (channel* cp, int v)
{
  int k;
  intitem* ip;
  Dt_t* adj;

  if (cp->cnt < 2) return;
  fprintf (stderr, "channel %d (%f,%f)\n", v, cp->p.p1, cp->p.p2);
  for (k=0;k<cp->cnt;k++) {
    adj = cp->G->vertices[k].adj_list;
    if (dtsize(adj) == 0) continue;
    putSeg (stderr, cp->seg_list[k]);
    fputs (" ->\n", stderr);
    for (ip = (intitem*)dtfirst(adj); ip; ip = (intitem*)dtnext(adj, ip)) {
      fputs ("     ", stderr);
      putSeg (stderr, cp->seg_list[ip->id]);
      fputs ("\n", stderr);
    }
  }
}
