deinterlace_frame_di_greedyh_planar (GstDeinterlaceMethod * method,
    const GstDeinterlaceField * history, guint history_count,
    GstVideoFrame * outframe, int cur_field_idx)
{
  GstDeinterlaceMethodGreedyH *self = GST_DEINTERLACE_METHOD_GREEDY_H (method);
  GstDeinterlaceMethodGreedyHClass *klass =
      GST_DEINTERLACE_METHOD_GREEDY_H_GET_CLASS (self);
  gint InfoIsOdd;
  gint RowStride;
  gint FieldHeight;
  gint Pitch;
  const guint8 *L1;
  const guint8 *L2;
  const guint8 *L3;
  const guint8 *L2P;
  guint8 *Dest;
  gint i;
  ScanlineFunction scanline;

  if (cur_field_idx + 2 > history_count || cur_field_idx < 1) {
    GstDeinterlaceMethod *backup_method;

    backup_method = g_object_new (gst_deinterlace_method_linear_get_type (),
        NULL);

    gst_deinterlace_method_setup (backup_method, method->vinfo);
    gst_deinterlace_method_deinterlace_frame (backup_method,
        history, history_count, outframe, cur_field_idx);

    g_object_unref (backup_method);
    return;
  }

  cur_field_idx += 2;

  for (i = 0; i < 3; i++) {
    InfoIsOdd = (history[cur_field_idx - 1].flags == PICTURE_INTERLACED_BOTTOM);
    RowStride = GST_VIDEO_FRAME_COMP_STRIDE (outframe, i);
    FieldHeight = GST_VIDEO_FRAME_COMP_HEIGHT (outframe, i) / 2;
    Pitch = RowStride * 2;

    if (i == 0)
      scanline = klass->scanline_planar_y;
    else
      scanline = klass->scanline_planar_uv;

    Dest = GST_VIDEO_FRAME_COMP_DATA (outframe, i);

    L1 = GST_VIDEO_FRAME_COMP_DATA (history[cur_field_idx - 2].frame, i);
    if (history[cur_field_idx - 2].flags & PICTURE_INTERLACED_BOTTOM)
      L1 += RowStride;

    L2 = GST_VIDEO_FRAME_COMP_DATA (history[cur_field_idx - 1].frame, i);
    if (history[cur_field_idx - 1].flags & PICTURE_INTERLACED_BOTTOM)
      L2 += RowStride;

    L3 = L1 + Pitch;
    L2P = GST_VIDEO_FRAME_COMP_DATA (history[cur_field_idx - 3].frame, i);
    if (history[cur_field_idx - 3].flags & PICTURE_INTERLACED_BOTTOM)
      L2P += RowStride;

    deinterlace_frame_di_greedyh_planar_plane (self, L1, L2, L3, L2P, Dest,
        RowStride, FieldHeight, Pitch, InfoIsOdd, scanline);
  }
}
