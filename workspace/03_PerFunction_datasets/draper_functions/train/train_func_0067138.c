gt_line_sketch(GtLine *line, GtCanvas *canvas, GtError *err)
{
  int i = 0, had_err = 0;
  gt_assert(line && canvas);
  had_err = gt_canvas_visit_line_pre(canvas, line, err);
  if (!had_err)
  {
    for (i = 0; !had_err && i < gt_array_size(line->blocks); i++) {
      GtBlock *block;
      block = *(GtBlock**) gt_array_get(line->blocks, i);
      had_err = gt_block_sketch(block, canvas, err);
    }
  }
  if (!had_err)
    had_err = gt_canvas_visit_line_post(canvas, line, err);
  return had_err;
}
