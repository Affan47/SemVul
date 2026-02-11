gt_esa_visitor_visit_branching_edge(GtESAVisitor *ev,
                                        bool firstsucc,
                                        unsigned long fd,
                                        unsigned long flb,
                                        GtESAVisitorInfo *finfo,
                                        unsigned long sd,
                                        unsigned long slb,
                                        unsigned long srb,
                                        GtESAVisitorInfo *sinfo,
                                        GtError *err)
{
  gt_error_check(err);
  gt_assert(ev && ev->c_class);
  if (ev->c_class->branchingedge_func != NULL)
    return ev->c_class->branchingedge_func(ev, firstsucc, fd, flb, finfo, sd,
                                           slb, srb, sinfo, err);
  return 0;
}
