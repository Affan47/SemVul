gt_canvas_visit_track_pre(GtCanvas *canvas, GtTrack *track, GtError *err)
{
  gt_assert(canvas && track);
  canvas->pvt->current_track = track;
  if (canvas->c_class->visit_track_pre)
    return canvas->c_class->visit_track_pre(canvas, track, err);
  else
    return 0;
}
