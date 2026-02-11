make_granulepos (GstTheoraParse * parse, gint64 keyframe, gint64 frame)
{
  gint64 iframe;

  if (keyframe == -1)
    keyframe = 0;


  if (!parse->is_old_bitstream)
    iframe = keyframe + 1;
  else
    iframe = keyframe;

  g_return_val_if_fail (frame >= keyframe, -1);
  g_return_val_if_fail (frame - keyframe < 1 << parse->shift, -1);

  return (iframe << parse->shift) + (frame - keyframe);
}
