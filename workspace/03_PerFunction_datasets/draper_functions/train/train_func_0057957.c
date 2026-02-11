set_internal_prefix_start(pIIR_DeclarativeRegion r, RegionStack &rstack)
{
  internal_prefix_start = qid(r, rstack, id_type()) + "_" + internal_prefix_base;
}
