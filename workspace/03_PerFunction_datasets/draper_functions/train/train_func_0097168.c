gst_mss_demux_restart_tasks (GstMssDemux * mssdemux)
{
  GSList *iter;
  for (iter = mssdemux->streams; iter; iter = g_slist_next (iter)) {
    GstMssDemuxStream *stream = iter->data;
    gst_uri_downloader_reset (stream->downloader);
    g_rec_mutex_unlock (&stream->download_lock);
  }
  g_rec_mutex_unlock (&mssdemux->stream_lock);
  for (iter = mssdemux->streams; iter; iter = g_slist_next (iter)) {
    GstMssDemuxStream *stream = iter->data;

    gst_data_queue_set_flushing (stream->dataqueue, FALSE);
    gst_task_start (stream->download_task);
  }
  gst_task_start (mssdemux->stream_task);
}
