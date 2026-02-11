cs2_autofocus (cs2_t * s)
{
  SANE_Status status;

  cs2_convert_options (s);

  cs2_scanner_ready (s, CS2_STATUS_READY);
  cs2_init_buffer (s);
  cs2_parse_cmd (s, "e0 00 a0 00 00 00 00 00 0d 00 00");
  cs2_pack_byte (s, (s->real_focusx >> 24) & 0xff);
  cs2_pack_byte (s, (s->real_focusx >> 16) & 0xff);
  cs2_pack_byte (s, (s->real_focusx >> 8) & 0xff);
  cs2_pack_byte (s, s->real_focusx & 0xff);
  cs2_pack_byte (s, (s->real_focusy >> 24) & 0xff);
  cs2_pack_byte (s, (s->real_focusy >> 16) & 0xff);
  cs2_pack_byte (s, (s->real_focusy >> 8) & 0xff);
  cs2_pack_byte (s, s->real_focusy & 0xff);
  cs2_parse_cmd (s, "00 00 00 00");
  status = cs2_issue_cmd (s);
  if (status)
    return status;

  status = cs2_execute (s);
  if (status)
    return status;

  cs2_scanner_ready (s, CS2_STATUS_READY);
  cs2_init_buffer (s);
  cs2_parse_cmd (s, "e1 00 c1 00 00 00 00 00 0d 00");
  s->n_recv = 13;
  status = cs2_issue_cmd (s);
  if (status)
    return status;

  s->focus =
    65536 * (256 * s->recv_buf[1] + s->recv_buf[2]) + 256 * s->recv_buf[3] +
    s->recv_buf[4];

  return status;
}
