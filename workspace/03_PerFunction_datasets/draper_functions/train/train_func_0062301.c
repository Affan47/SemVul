gst_mpegvideoparse_chain_reverse (MpegVideoParse * mpegvideoparse,
    gboolean discont, GstBuffer * buf)
{
  GstFlowReturn res = GST_FLOW_OK;


  if (G_UNLIKELY (discont)) {
    GST_DEBUG_OBJECT (mpegvideoparse, "received discont,gathering buffers");

    while (mpegvideoparse->gather) {
      GstBuffer *gbuf;
      guint keyframeidx;

      gbuf = GST_BUFFER_CAST (mpegvideoparse->gather->data);

      mpegvideoparse->gather =
          g_list_delete_link (mpegvideoparse->gather, mpegvideoparse->gather);

      mpegvideoparse->decode = g_list_prepend (mpegvideoparse->decode, gbuf);

      GST_DEBUG_OBJECT (mpegvideoparse, "copied decoding buffer %p, len %d",
          gbuf, g_list_length (mpegvideoparse->decode));


      while ((keyframeidx = scan_keyframe (mpegvideoparse)) != -1) {
        GST_DEBUG_OBJECT (mpegvideoparse, "copied keyframe at %u", keyframeidx);
        res = gst_mpegvideoparse_flush_decode (mpegvideoparse, keyframeidx);
      }
    }
  }

  if (buf) {

    GST_DEBUG_OBJECT (mpegvideoparse, "gathering buffer %p, size %u", buf,
        GST_BUFFER_SIZE (buf));
    mpegvideoparse->gather = g_list_prepend (mpegvideoparse->gather, buf);
  }

  return res;
}
