gt_strgraph_spell(GtStrgraph *strgraph, unsigned long min_path_depth,
    unsigned long min_contig_length, bool showpaths, const char *indexname,
    const char *suffix, const GtEncseq *encseq, bool delay_reads_mapping,
    bool show_progressbar, GtLogger *logger)
{
  FILE *outfp = NULL;
  GtFile *gt_outfp = NULL;
  GtStr *filename;

  gt_assert(strgraph != NULL);
  filename = gt_str_new_cstr(indexname);
  gt_str_append_cstr(filename, suffix);

  outfp = gt_fa_xfopen(gt_str_get(filename), "w");
  gt_outfp = gt_file_new_from_fileptr(outfp);

  if (!delay_reads_mapping)
    gt_strgraph_show_contigs(strgraph, min_path_depth, min_contig_length,
        showpaths, gt_outfp, encseq, show_progressbar, logger);
  else
    gt_strgraph_show_contigpaths(strgraph, min_path_depth, gt_outfp,
        show_progressbar);

  gt_str_delete(filename);
  gt_file_delete(gt_outfp);
}
