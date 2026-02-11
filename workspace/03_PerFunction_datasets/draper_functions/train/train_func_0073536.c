is_granulepos_keyframe_daala (GstOggStream * pad, gint64 granulepos)
{
  gint64 frame_mask;

  if (granulepos == (gint64) - 1)
    return FALSE;

  frame_mask = (1 << pad->granuleshift) - 1;

  return ((granulepos & frame_mask) == 0);
}
