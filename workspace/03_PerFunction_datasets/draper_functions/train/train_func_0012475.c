convert_hline_generic (paintinfo * p, GstVideoFrame * frame, int y)
{
  const GstVideoFormatInfo *finfo, *uinfo;
  gint line, offset, i, width, height, bits;
  guint n_lines;
  gpointer dest;

  finfo = frame->info.finfo;
  uinfo = gst_video_format_get_info (finfo->unpack_format);

  width = GST_VIDEO_FRAME_WIDTH (frame);
  height = GST_VIDEO_FRAME_HEIGHT (frame);

  bits = GST_VIDEO_FORMAT_INFO_DEPTH (uinfo, 0);

  n_lines = p->n_lines;
  offset = p->offset;
  line = y % n_lines;
  dest = p->lines[line];

  if (bits == 16) {

    for (i = 0; i < width; i++) {
      p->tmpline_u16[i * 4 + 0] = TO_16 (p->tmpline[i * 4 + 0]);
      p->tmpline_u16[i * 4 + 1] = TO_16 (p->tmpline[i * 4 + 1]);
      p->tmpline_u16[i * 4 + 2] = TO_16 (p->tmpline[i * 4 + 2]);
      p->tmpline_u16[i * 4 + 3] = TO_16 (p->tmpline[i * 4 + 3]);
    }
    memcpy (dest, p->tmpline_u16, width * 8);
  } else {
    memcpy (dest, p->tmpline, width * 4);
  }

  if (line - offset == n_lines - 1) {
    gpointer lines[8];
    guint idx;

    y -= n_lines - 1;

    for (i = 0; i < n_lines; i++) {
      idx = CLAMP (y + i + offset, 0, height - 1);

      GST_DEBUG ("line %d, %d, idx %d", i, y + i + offset, idx);
      lines[i] = p->lines[idx % n_lines];
    }

    if (p->subsample)
      gst_video_chroma_resample (p->subsample, lines, width);

    for (i = 0; i < n_lines; i++) {
      idx = y + i + offset;
      if (idx > height - 1)
        break;
      GST_DEBUG ("pack line %d", idx);
      finfo->pack_func (finfo, GST_VIDEO_PACK_FLAG_NONE,
          lines[i], 0, frame->data, frame->info.stride,
          frame->info.chroma_site, idx, width);
    }
  }
}
