directional_flips (uint8_t *sq, int inc, int color, int oppcol)
{
  uint8_t *pt = sq + inc;
  if (*pt == oppcol) {
    pt += inc;
    if (*pt == oppcol) {
      pt += inc;
      if (*pt == oppcol) {
        pt += inc;
        if (*pt == oppcol) {
          pt += inc;
          if (*pt == oppcol) {
            pt += inc;
            if (*pt == oppcol) {
              pt += inc;
            }
          }
        }
      }
    }
    if (*pt == color) {
      pt -= inc;
      do {
        *pt = color;
        *(flip_stack++) = pt;
        pt -= inc;
      } while (pt != sq);
    }
  }
}
