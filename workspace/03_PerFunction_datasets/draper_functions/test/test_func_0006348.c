gst_avi_demux_read_subindexes_pull (GstAviDemux * avi)
{
  guint32 tag;
  GstBuffer *buf;
  gint i, n;

  GST_DEBUG_OBJECT (avi, "read subindexes for %d streams", avi->num_streams);

  for (n = 0; n < avi->num_streams; n++) {
    GstAviStream *stream = &avi->stream[n];

    if (stream->indexes == NULL)
      continue;

    for (i = 0; stream->indexes[i] != GST_BUFFER_OFFSET_NONE; i++) {
      if (gst_riff_read_chunk (GST_ELEMENT_CAST (avi), avi->sinkpad,
              &stream->indexes[i], &tag, &buf) != GST_FLOW_OK)
        continue;
      else if ((tag != GST_MAKE_FOURCC ('i', 'x', '0' + stream->num / 10,
                  '0' + stream->num % 10)) &&
          (tag != GST_MAKE_FOURCC ('0' + stream->num / 10,
                  '0' + stream->num % 10, 'i', 'x'))) {


        GST_WARNING_OBJECT (avi, "Not an ix## chunk (%" GST_FOURCC_FORMAT ")",
            GST_FOURCC_ARGS (tag));
        gst_buffer_unref (buf);
        continue;
      }

      if (!gst_avi_demux_parse_subindex (avi, stream, buf))
        continue;
    }

    g_free (stream->indexes);
    stream->indexes = NULL;
  }

  avi->have_index = gst_avi_demux_do_index_stats (avi);
}
