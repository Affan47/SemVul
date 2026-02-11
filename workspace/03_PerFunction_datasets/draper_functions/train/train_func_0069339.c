v128_left_shift(v128_t *x, int shift) {
  int i;
  const int base_index = shift >> 5;
  const int bit_index = shift & 31;

  if (shift > 127) {
    v128_set_to_zero(x);
    return;
  }

  if (bit_index == 0) {
    for (i=0; i < 4 - base_index; i++)
      x->v32[i] = x->v32[i+base_index];
  } else {
    for (i=0; i < 4 - base_index - 1; i++)
      x->v32[i] = (x->v32[i+base_index] >> bit_index) ^
	(x->v32[i+base_index+1] << (32 - bit_index));
    x->v32[4 - base_index-1] = x->v32[4-1] >> bit_index;
  }


  for (i = 4 - base_index; i < 4; i++)
    x->v32[i] = 0;

}
