gt_strgraph_show_edge_lengths_distribution(const GtStrgraph *strgraph,
    const char *indexname, const char *suffix)
{
  GtDiscDistri *d = gt_disc_distri_new();
  GtStrgraphVnum i;
  GtStrgraphVEdgenum j;

  GtFile *outfp = gt_strgraph_get_file(indexname, suffix, true, false);

  gt_assert(strgraph != NULL);
  gt_assert(sizeof (unsigned long) >= sizeof (GtStrgraphLength));
  for (i = 0; i < GT_STRGRAPH_NOFVERTICES(strgraph); i++)
  {
    for (j = 0; j < GT_STRGRAPH_V_NOFEDGES(strgraph, i); j++)
    {
      gt_disc_distri_add(d,
          (unsigned long)GT_STRGRAPH_EDGE_LEN(strgraph, i, j));
    }
  }
  gt_file_xprintf(outfp, "# length nofedges\n");
  gt_disc_distri_foreach(d,
     (GtDiscDistriIterFunc) gt_strgraph_show_disc_distri_datapoint, outfp);
  gt_disc_distri_delete(d);
  gt_file_delete(outfp);
}
