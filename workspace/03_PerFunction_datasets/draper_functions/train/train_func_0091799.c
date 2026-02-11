gst_video_crop_transform_packed_complex (GstVideoCrop * vcrop,
    GstVideoFrame * in_frame, GstVideoFrame * out_frame)
{
  guint8 *in_data, *out_data;
  guint i, dx;
  gint width, height;
  gint in_stride;
  gint out_stride;

  width = GST_VIDEO_FRAME_WIDTH (out_frame);
  height = GST_VIDEO_FRAME_HEIGHT (out_frame);

  in_data = GST_VIDEO_FRAME_PLANE_DATA (in_frame, 0);
  out_data = GST_VIDEO_FRAME_PLANE_DATA (out_frame, 0);

  in_stride = GST_VIDEO_FRAME_PLANE_STRIDE (in_frame, 0);
  out_stride = GST_VIDEO_FRAME_PLANE_STRIDE (out_frame, 0);

  in_data += vcrop->crop_top * in_stride;


  in_data += ROUND_DOWN_2 (vcrop->crop_left) *
      GST_VIDEO_FRAME_COMP_PSTRIDE (in_frame, 0);

  dx = width * GST_VIDEO_FRAME_COMP_PSTRIDE (out_frame, 0);


  if ((vcrop->crop_left % 2) != 0) {
    for (i = 0; i < height; ++i) {
      gint j;

      memcpy (out_data, in_data, dx);


      for (j = vcrop->macro_y_off; j < out_stride - 2; j += 2)
        out_data[j] = in_data[j + 2];

      in_data += in_stride;
      out_data += out_stride;
    }
  } else {
    for (i = 0; i < height; ++i) {
      memcpy (out_data, in_data, dx);
      in_data += in_stride;
      out_data += out_stride;
    }
  }
}
