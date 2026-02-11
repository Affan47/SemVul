gff3_visitor_region_node(GtNodeVisitor *nv, GtRegionNode *rn,
                                    GT_UNUSED GtError *err)
{
  GtGFF3Visitor *gff3_visitor;
  gt_error_check(err);
  gff3_visitor = gff3_visitor_cast(nv);
  gt_assert(nv && rn);
  gff3_version_string(nv);
  gt_file_xprintf(gff3_visitor->outfp, "%s   %s %lu %lu\n",
                  GT_GFF_SEQUENCE_REGION,
                  gt_str_get(gt_genome_node_get_seqid((GtGenomeNode*) rn)),
                  gt_genome_node_get_start((GtGenomeNode*) rn),
                  gt_genome_node_get_end((GtGenomeNode*) rn));
  return 0;
}
