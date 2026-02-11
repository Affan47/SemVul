unblock_subtitle (GstSubtitleOverlay * self)
{
  if (self->subtitle_block_id) {
    gst_pad_remove_probe (self->subtitle_block_pad, self->subtitle_block_id);
    self->subtitle_sink_blocked = FALSE;
    self->subtitle_block_id = 0;
  }
}
