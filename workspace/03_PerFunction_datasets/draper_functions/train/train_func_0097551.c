snp_annotator_stream_process_current_gene(GtSNPAnnotatorStream *sas,
                                                     GtError *err)
{
  int had_err = 0;
  unsigned long i;
  unsigned long nof_genes = gt_array_size(sas->cur_gene_set);
  gt_error_check(err);

  if (gt_queue_size(sas->snps) > 0) {

    gt_assert(gt_queue_size(sas->outqueue) == 0);

    for (i = 0; !had_err && i < nof_genes; i++) {
      GtNodeVisitor *sav;
      GtFeatureNode *gene;
      gene = *(GtFeatureNode**) gt_array_get(sas->cur_gene_set, i);
      sav = gt_snp_annotator_visitor_new(gene, sas->tt, sas->rmap, err);
      if (!sav)
        had_err = -1;
      if (!had_err) {
        if (i < nof_genes-1) {
          had_err = gt_queue_iterate(sas->snps,
                                     snp_annotator_stream_process_snp,
                                     sav, err);
        } else {
          while (!had_err && gt_queue_size(sas->snps) > 0) {
            GtFeatureNode *snp = (GtFeatureNode*) gt_queue_get(sas->snps);
            had_err = gt_genome_node_accept((GtGenomeNode*) snp, sav, err);
            gt_queue_add(sas->outqueue, snp);
            gt_genome_node_delete((GtGenomeNode*) snp);
          }
        }
        gt_node_visitor_delete(sav);
      }
      gt_genome_node_delete((GtGenomeNode*) gene);
    }
  } else {

    for (i = 0; !had_err && i < nof_genes; i++) {
      gt_genome_node_delete(*(GtGenomeNode**) gt_array_get(sas->cur_gene_set,
                                                           i));
    }
  }
  gt_assert(gt_queue_size(sas->snps) == 0);
  gt_array_reset(sas->cur_gene_set);
  return had_err;
}
