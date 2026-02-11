gt_strgraph_dot_bi_show(const GtStrgraph *strgraph, GtFile *outfp,
    bool show_progressbar)
{
  unsigned long sn1, sn2;
  GtStrgraphVnum i;
  GtStrgraphVEdgenum j;
  bool is_e1, is_e2;
  unsigned long long progress = 0;

  gt_assert(strgraph != NULL);

  if (show_progressbar)
    gt_progressbar_start(&progress,
        (unsigned long long)GT_STRGRAPH_NOFVERTICES(strgraph));

  gt_file_xprintf(outfp, GT_STRGRAPH_DOT_BI_HEADER);
  for (i = 0; i < GT_STRGRAPH_NOFVERTICES(strgraph); i++) {
    if (GT_STRGRAPH_V_OUTDEG(strgraph, i) > 0)
    {
      sn1 = GT_STRGRAPH_V_READNUM(i);
      is_e1 = GT_STRGRAPH_V_IS_E(i);
      for (j = 0; j < GT_STRGRAPH_V_NOFEDGES(strgraph, i); j++)
      {
        if (!GT_STRGRAPH_EDGE_IS_REDUCED(strgraph, i, j))
        {
          sn2 = GT_STRGRAPH_V_READNUM(GT_STRGRAPH_EDGE_DEST(strgraph, i, j));
          is_e2 = GT_STRGRAPH_V_IS_E(GT_STRGRAPH_EDGE_DEST(strgraph, i, j));
          if (is_e1 && is_e2) {
            gt_strgraph_dot_bi_show_edge(outfp, sn1, false, sn2, true);
          }
          else if ((is_e1 && !is_e2) && (sn1 < sn2)) {
            gt_strgraph_dot_bi_show_edge(outfp, sn1, false, sn2, false);
          }
          else if ((!is_e1 && is_e2) && (sn1 > sn2)) {
            gt_strgraph_dot_bi_show_edge(outfp, sn1, true, sn2, true);
          }


        }
      }
    }
    if (show_progressbar)
      progress++;
  }
  gt_file_xprintf(outfp, GT_STRGRAPH_DOT_FOOTER);

  if (show_progressbar)
    gt_progressbar_stop();
}
