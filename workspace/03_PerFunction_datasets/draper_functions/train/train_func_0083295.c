stream_evaluator_lua_evaluate(lua_State *L)
{
  GtStreamEvaluator **stream_evaluator;
  GtNodeVisitor **genome_visitor;
  GtError *err;
  stream_evaluator = check_stream_evaluator(L);
  if (lua_gettop(L) >= 2) {
    genome_visitor = check_genome_visitor(L, 2);
  }
  else
    genome_visitor = NULL;
  err = gt_error_new();
  if (gt_stream_evaluator_evaluate(*stream_evaluator, false, false, false,
                                   genome_visitor ? *genome_visitor : NULL,
                                   err)) {
    return gt_lua_error(L, err);
  }
  gt_error_delete(err);
  return 0;
}
