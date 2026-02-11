remove_node(GtGenomeNode *genome_node, GtQueue *genome_nodes)
{
  gt_assert(genome_node && genome_nodes);
  gt_queue_remove(genome_nodes, genome_node);
}
