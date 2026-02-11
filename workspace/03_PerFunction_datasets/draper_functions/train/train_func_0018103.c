eh_frame_estimate_size_before_relax (fragS *frag)
{
  offsetT diff;
  int ca = frag->fr_subtype >> 3;
  int ret;

  diff = resolve_symbol_value (frag->fr_symbol);

  gas_assert (ca > 0);
  diff /= ca;
  if (diff < 0x40)
    ret = 0;
  else if (diff < 0x100)
    ret = 1;
  else if (diff < 0x10000)
    ret = 2;
  else
    ret = 4;

  frag->fr_subtype = (frag->fr_subtype & ~7) | ret;

  return ret;
}
