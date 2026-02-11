tsmux_write_section (TsMux * mux, TsMuxSection * section)
{
  guint8 *cur_in;
  guint payload_remain;
  guint payload_len, payload_offs;
  TsMuxPacketInfo *pi;

  pi = &section->pi;

  pi->packet_start_unit_indicator = TRUE;

  cur_in = section->data;
  payload_remain = pi->stream_avail;

  while (payload_remain > 0) {
    if (pi->packet_start_unit_indicator) {

      pi->stream_avail++;

      if (!tsmux_write_ts_header (mux->packet_buf, pi,
              &payload_len, &payload_offs)) {
        pi->stream_avail--;
        return FALSE;
      }
      pi->stream_avail--;


      mux->packet_buf[payload_offs] = 0x00;

      payload_offs++;
      payload_len--;
      pi->packet_start_unit_indicator = FALSE;
    } else {
      if (!tsmux_write_ts_header (mux->packet_buf, pi,
              &payload_len, &payload_offs))
        return FALSE;
    }

    TS_DEBUG ("Outputting %d bytes to section. %d remaining after",
        payload_len, payload_remain - payload_len);

    memcpy (mux->packet_buf + payload_offs, cur_in, payload_len);

    cur_in += payload_len;
    payload_remain -= payload_len;

    if (G_UNLIKELY (!tsmux_packet_out (mux))) {
      mux->new_pcr = -1;
      return FALSE;
    }
    mux->new_pcr = -1;
  }

  return TRUE;
}
