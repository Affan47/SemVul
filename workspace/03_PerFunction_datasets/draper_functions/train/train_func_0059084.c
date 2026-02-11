cs2_set_boundary (cs2_t *s)
{
  SANE_Status status;
  int i_boundary;
  unsigned long lvalue;


  cs2_scanner_ready (s, CS2_STATUS_READY);
  cs2_init_buffer (s);
  cs2_parse_cmd (s, "2a 00 88 00 00 03");
  cs2_pack_byte (s, ((4 + s->n_frames * 16) >> 16) & 0xff);
  cs2_pack_byte (s, ((4 + s->n_frames * 16) >> 8) & 0xff);
  cs2_pack_byte (s, (4 + s->n_frames * 16) & 0xff);
  cs2_parse_cmd (s, "00");

  cs2_pack_byte (s, ((4 + s->n_frames * 16) >> 8) & 0xff);
  cs2_pack_byte (s, (4 + s->n_frames * 16) & 0xff);
  cs2_pack_byte (s, s->n_frames);
  cs2_pack_byte (s, s->n_frames);
  for (i_boundary = 0; i_boundary < s->n_frames; i_boundary++)
    {
      lvalue = s->frame_offset * i_boundary + s->subframe / s->unit_mm;
      cs2_pack_byte (s, (lvalue >> 24) & 0xff);
      cs2_pack_byte (s, (lvalue >> 16) & 0xff);
      cs2_pack_byte (s, (lvalue >> 8) & 0xff);
      cs2_pack_byte (s, lvalue & 0xff);

      lvalue = 0;
      cs2_pack_byte (s, (lvalue >> 24) & 0xff);
      cs2_pack_byte (s, (lvalue >> 16) & 0xff);
      cs2_pack_byte (s, (lvalue >> 8) & 0xff);
      cs2_pack_byte (s, lvalue & 0xff);

      lvalue = s->frame_offset * i_boundary + s->subframe / s->unit_mm + s->frame_offset - 1;
      cs2_pack_byte (s, (lvalue >> 24) & 0xff);
      cs2_pack_byte (s, (lvalue >> 16) & 0xff);
      cs2_pack_byte (s, (lvalue >> 8) & 0xff);
      cs2_pack_byte (s, lvalue & 0xff);

      lvalue = s->boundaryx - 1;
      cs2_pack_byte (s, (lvalue >> 24) & 0xff);
      cs2_pack_byte (s, (lvalue >> 16) & 0xff);
      cs2_pack_byte (s, (lvalue >> 8) & 0xff);
      cs2_pack_byte (s, lvalue & 0xff);
    }
  status = cs2_issue_cmd (s);
  if (status)
    return status;

  return SANE_STATUS_GOOD;
}
