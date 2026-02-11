compute_fast_clear_color_bits(const union gl_color_union *color)
{
   uint32_t bits = 0;
   for (int i = 0; i < 4; i++) {
      if (color->f[i] != 0.0)
         bits |= 1 << (GEN7_SURFACE_CLEAR_COLOR_SHIFT + (3 - i));
   }
   return bits;
}
