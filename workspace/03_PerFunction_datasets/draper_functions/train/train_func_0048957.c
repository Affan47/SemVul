gt_custom_track_sketch(GtCustomTrack *ctrack, GtCanvas *canvas,
                           GtError *err)
{
  gt_assert(ctrack && canvas);
  return gt_canvas_visit_custom_track(canvas, ctrack, err);
}
