gst_ogg_mux_make_fistail (GstOggMux * mux, ogg_stream_state * os)
{
  GST_DEBUG_OBJECT (mux, "Creating fistail");

  gst_ogg_mux_submit_skeleton_header_packet (mux, os,
      gst_buffer_new_and_alloc (0), 0, 1);
}
