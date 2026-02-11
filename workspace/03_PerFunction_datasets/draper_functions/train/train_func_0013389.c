gt_strgraph_spm_show(const GtStrgraph *strgraph, GtFile *outfp)
{
  unsigned long sn1, sn2;
  GtStrgraphVnum i, v2;
  GtStrgraphLength spm_len;
  GtStrgraphVEdgenum j;
  bool is_e1, is_e2;

  for (i = 0; i < GT_STRGRAPH_NOFVERTICES(strgraph); i++)
  {
    if (GT_STRGRAPH_V_OUTDEG(strgraph, i) > 0)
    {
      sn1 = GT_STRGRAPH_V_READNUM(i);
      is_e1 = GT_STRGRAPH_V_IS_E(i);
      for (j = 0; j < GT_STRGRAPH_V_NOFEDGES(strgraph, i); j++)
      {
        if (!GT_STRGRAPH_EDGE_IS_REDUCED(strgraph, i, j))
        {
          v2 = GT_STRGRAPH_EDGE_DEST(strgraph, i, j);
          sn2 = GT_STRGRAPH_V_READNUM(v2);
          spm_len = GT_STRGRAPH_SEQLEN(strgraph, sn2) -
            GT_STRGRAPH_EDGE_LEN(strgraph, i, j);
          is_e2 = GT_STRGRAPH_V_IS_E(v2);
          if ((is_e1 && is_e2) || (is_e1 && !is_e2 && (sn1 <= sn2)) ||
              (!is_e1 &&  is_e2 && (sn1 >= sn2)))
          {


            gt_file_xprintf(outfp, "%lu %s %lu %s "FormatGtStrgraphLength"\n",
                sn1, is_e1 ? "+" : "-",
                sn2, is_e2 ? "+" : "-",
                PRINTGtStrgraphLengthcast(spm_len));
          }
        }
      }
    }
  }
}
