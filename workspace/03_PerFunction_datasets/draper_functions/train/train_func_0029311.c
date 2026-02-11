sg_special_set(bv_special *specials, char ch,
                           const enum tile_special_type *index,
                           bool rivers_overlay)
{
  int i, bin;
  const char *pch = strchr(hex_chars, ch);

  if (!pch || ch == '\0') {
    log_sg("Unknown hex value: '%c' (%d)", ch, ch);
    bin = 0;
  } else {
    bin = pch - hex_chars;
  }

  for (i = 0; i < 4; i++) {
    enum tile_special_type sp = index[i];

    if (sp >= S_LAST) {
      continue;
    }
    if (rivers_overlay && sp != S_RIVER) {
      continue;
    }

    if (bin & (1 << i)) {
      set_special(specials, sp);
    }
  }
}
