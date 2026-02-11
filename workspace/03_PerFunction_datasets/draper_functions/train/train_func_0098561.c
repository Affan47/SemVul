gt_custom_track_get_title(GtCustomTrack *ctrack)
{
  gt_assert(ctrack && ctrack->c_class);
  return ctrack->c_class->get_title(ctrack);
}
