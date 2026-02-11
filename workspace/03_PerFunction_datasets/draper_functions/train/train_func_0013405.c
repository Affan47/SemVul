gt_strgraph_show_contigs(GtStrgraph *strgraph,
    unsigned long min_path_depth, unsigned long min_contig_length,
    bool showpaths, GtFile *outfp, const GtEncseq *encseq,
    bool show_progressbar, GtLogger *logger)
{
  GtStrgraphSpellData sdata;

  gt_strgraph_set_encseq(strgraph, encseq);
  sdata.cw = gt_contigs_writer_new(encseq, outfp, showpaths);
  sdata.strgraph = strgraph;
  sdata.total_depth = 0;
  sdata.current_depth = 0;
  sdata.current_length = 0;
  sdata.contignum = 0;
  sdata.min_depth = min_path_depth;
  sdata.min_length = min_contig_length;

  gt_strgraph_traverse(strgraph, gt_strgraph_spell_vertex,
      gt_strgraph_spell_edge, &sdata, show_progressbar);


  if (sdata.current_depth >= min_path_depth &&
      sdata.current_length >= min_contig_length)
    gt_contigs_writer_write(sdata.cw);
  else
    gt_contigs_writer_abort(sdata.cw);

  gt_log_log("traversed edges = %lu", sdata.total_depth);
  gt_log_log("numofcontigs = %lu", sdata.contignum);

  if (sdata.contignum > 0)
    gt_contigs_writer_show_stats(sdata.cw, logger);
  else
    gt_logger_log(logger, "no contigs respect the given cutoff parameters");

  gt_contigs_writer_delete(sdata.cw);
}
