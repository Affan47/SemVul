draw_sprshade (const a_sprite *sprite, a_pixel *dest)
{
  a_pixel	*cur = dest;
  a_u8		*pc;
  a_u8		*epc;

  assert (sprite->all.kind == S_RLE_SHADE);

  pc = sprite->shade.code;
  epc = sprite->shade.end_code;

  while (pc < epc) {
    unsigned m, n;
    m = *pc++;
    n = *pc++;
    if (n == 0 && m == 0 && *pc == 0) {
      ++pc;
      cur += sprite->shade.line_skip;
    } else {

      cur += m;

      for (; n; --n)
	*cur++ = *pc++;

      for (m = *pc++; m; --m) {
	*cur = sprite->shade.glenz[*cur];
	++cur;
      }
    }
  }
}
