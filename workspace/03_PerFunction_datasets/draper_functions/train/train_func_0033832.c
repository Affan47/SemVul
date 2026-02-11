gt_line_breaker_register_block(GtLineBreaker *lb, GtLine *line,
                                    GtBlock *block, GtError *err)
{
  gt_assert(lb && lb->c_class && line && block);
  return lb->c_class->register_block(lb, line, block, err);
}
