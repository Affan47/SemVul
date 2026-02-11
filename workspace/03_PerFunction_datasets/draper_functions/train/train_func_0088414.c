shader_fade_and_move_up (GstBaseAudioVisualizer * scope, const guint8 * s,
    guint8 * d)
{
  guint i, j, bpf = scope->bpf;
  guint bpl = 4 * scope->width;
  guint r = (scope->shade_amount >> 16) & 0xff;
  guint g = (scope->shade_amount >> 8) & 0xff;
  guint b = (scope->shade_amount >> 0) & 0xff;

  for (j = 0, i = bpl; i < bpf;) {
    SHADE2 (d, s, j, i, r, g, b);
  }
}
