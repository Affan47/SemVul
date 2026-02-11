gst_mpegvideoparse_flush (MpegVideoParse * mpegvideoparse)
{
  GST_DEBUG_OBJECT (mpegvideoparse, "mpegvideoparse: flushing");

  mpegvideoparse->next_offset = GST_BUFFER_OFFSET_NONE;

  g_list_foreach (mpegvideoparse->gather, (GFunc) gst_mini_object_unref, NULL);
  g_list_free (mpegvideoparse->gather);
  mpegvideoparse->gather = NULL;
  g_list_foreach (mpegvideoparse->decode, (GFunc) gst_mini_object_unref, NULL);
  g_list_free (mpegvideoparse->decode);
  mpegvideoparse->decode = NULL;
  mpeg_packetiser_flush (&mpegvideoparse->packer);

  mpv_clear_pending_segs (mpegvideoparse);
}
