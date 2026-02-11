finish_global_and_expr_for_bb (basic_block bb)
{
  av_set_clear (&BB_AV_SET (bb));
  BB_AV_LEVEL (bb) = 0;
}
