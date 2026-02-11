gfs_draw_refined_boundaries (GfsDomain * domain, FILE * fp)
{
  guint depth, level;
  g_return_if_fail (domain != NULL);
  g_return_if_fail (fp != NULL);

  depth = gfs_domain_depth (domain);
  for (level = 1; level <= depth; level++) {
    guint count = 0;

    gfs_domain_cell_traverse (domain,
			     FTT_PRE_ORDER, FTT_TRAVERSE_LEVEL, level,
			     (FttCellTraverseFunc) count_face, &count);
    if (count > 0) {
      fprintf (fp, "(geometry \"refine_%u_%u\" = \n", level - 1, level);
      fputs ("LIST{\n", fp);
      gfs_domain_cell_traverse (domain,
			       FTT_PRE_ORDER, FTT_TRAVERSE_LEVEL, level,
			       (FttCellTraverseFunc) draw_face, fp);
      fputs ("}\n)\n", fp);
    }
  }
}
