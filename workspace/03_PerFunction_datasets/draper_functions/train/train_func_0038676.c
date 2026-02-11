set_word(_u32 position, _u32 val) {
  _u32 f, roff;

  if (!cur_fuzzable) return;
  position %= cur_fuzzable;

  f = lookup_file(position, 1, &roff);
  load_data(f);

  infile[f].dirty = 1;

  if (roff + 1 < infile[f].cur_len)
    *(_u16*)(infile[f].data + roff) = val;
  else {

    infile[f].data[roff] = val;
    set_byte(position + 1, val >> 8);
  }
}
