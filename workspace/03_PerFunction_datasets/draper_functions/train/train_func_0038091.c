gt_esa_visitor_class_new(size_t size,
                         GtESAVisitorFreeFunc free,
                         GtESAVisitorLeafEdgeFunc leafedge_func,
                         GtESAVisitorBranchingEdgeFunc branchingedge_func,
                         GtESAVisitorLCPIntervalFunc lcpinterval_func,
                         GtESAVisitorInfoCreatorFunc create_info_func,
                         GtESAVisitorInfoDestructorFunc delete_info_func)
{
  GtESAVisitorClass *c_class;
  gt_assert(size);
  c_class = gt_class_alloc(sizeof *c_class);
  c_class->size = size;
  c_class->free = free;
  c_class->leafedge_func = leafedge_func;
  c_class->branchingedge_func = branchingedge_func;
  c_class->lcpinterval_func = lcpinterval_func;
  c_class->create_info_func = create_info_func;
  c_class->delete_info_func = delete_info_func;
  return c_class;
}
