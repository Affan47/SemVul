gst_video_rate_reset (GstVideoRate * videorate)
{
  GST_DEBUG_OBJECT (videorate, "resetting internal variables");

  videorate->in = 0;
  videorate->out = 0;
  videorate->base_ts = 0;
  videorate->out_frame_count = 0;
  videorate->drop = 0;
  videorate->dup = 0;
  videorate->next_ts = GST_CLOCK_TIME_NONE;
  videorate->last_ts = GST_CLOCK_TIME_NONE;
  videorate->discont = TRUE;
  videorate->average = 0;
  gst_video_rate_swap_prev (videorate, NULL, 0);

  gst_segment_init (&videorate->segment, GST_FORMAT_TIME);
}
