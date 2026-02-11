psmux_write_stream_packet (PsMux * mux, PsMuxStream * stream)
{
  gboolean res;

  g_return_val_if_fail (mux != NULL, FALSE);
  g_return_val_if_fail (stream != NULL, FALSE);


  {
    guint64 ts = psmux_stream_get_pts (stream);
    if (ts != -1)
      mux->pts = ts;
  }

  if (mux->pts - mux->pack_hdr_pts > PSMUX_PACK_HDR_INTERVAL
      || mux->pes_cnt % mux->pack_hdr_freq == 0) {


    if (mux->pts != -1 && mux->pts > mux->bit_pts
        && mux->pts - mux->bit_pts > PSMUX_BITRATE_CALC_INTERVAL) {

      mux->bit_rate =
          gst_util_uint64_scale (mux->bit_size, 8 * CLOCKBASE,
          (mux->pts - mux->bit_pts));

      mux->bit_size = 0;
      mux->bit_pts = mux->pts;
    }

    psmux_write_pack_header (mux);
    mux->pack_hdr_pts = mux->pts;
  }

  if (mux->pes_cnt % mux->sys_hdr_freq == 0) {

    psmux_write_system_header (mux);
    mux->sys_hdr_pts = mux->pts;
  }

  if (mux->pes_cnt % mux->psm_freq == 0) {

    psmux_write_program_stream_map (mux);
    mux->psm_pts = mux->pts;
  }


  if (!(mux->packet_bytes_written =
          psmux_stream_get_data (stream, mux->packet_buf,
              mux->pes_max_payload + PSMUX_PES_MAX_HDR_LEN))) {
    return FALSE;
  }

  res = psmux_packet_out (mux);
  if (!res) {
    GST_DEBUG_OBJECT (mux, "packet write false");
    return FALSE;
  }

  mux->pes_cnt += 1;

  return res;
}
