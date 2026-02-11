color_transform (CogFrame * frame, void *_dest, int component, int j)
{
  uint8_t *dest = _dest;
  uint8_t *src_y;
  uint8_t *src_u;
  uint8_t *src_v;
  uint8_t *table;
  int i;

  table = COG_OFFSET (frame->virt_priv2, component * 0x1000000);

  src_y = cog_virt_frame_get_line (frame->virt_frame1, 0, j);
  src_u = cog_virt_frame_get_line (frame->virt_frame1, 1, j);
  src_v = cog_virt_frame_get_line (frame->virt_frame1, 2, j);

  for (i = 0; i < frame->width; i++) {
    dest[i] = table[(src_y[i] << 16) | (src_u[i] << 8) | (src_v[i])];
  }
}
