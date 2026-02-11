gt_genome_node_class_new(size_t size,
                         GtGenomeNodeFreeFunc free,
                         GtGenomeNodeSetSeqidFunc get_seqid,
                         GtGenomeNodeGetIdstrFunc get_idstr,
                         GtGenomeNodeGetRangeFunc get_range,
                         GtGenomeNodeSetRangeFunc set_range,
                         GtGenomeNodeChangeSeqidFunc change_seqid,
                         GtGenomeNodeAcceptFunc accept)
{
  GtGenomeNodeClass *c_class;
  gt_assert(size);
  c_class = gt_class_alloc(sizeof *c_class);
  c_class->size = size;
  c_class->free = free;
  c_class->get_seqid = get_seqid;
  c_class->get_idstr = get_idstr;
  c_class->get_range = get_range;
  c_class->set_range = set_range;
  c_class->change_seqid = change_seqid;
  c_class->accept = accept;
  return c_class;
}
