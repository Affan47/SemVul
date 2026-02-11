desaturate() {

  if (!w() || !h() || !d() || !array) return;


  if (d() < 3) return;


  uncache();


  uchar		*new_array,
		*new_ptr;
  int		new_d;

  new_d     = d() - 2;
  new_array = new uchar[h() * w() * new_d];


  const uchar	*old_ptr;
  int		x, y;
  int   line_i = ld() ? ld() - (w()*d()) : 0;

  for (new_ptr = new_array, old_ptr = array, y = 0; y < h(); y ++, old_ptr += line_i)
    for (x = 0; x < w(); x ++, old_ptr += d()) {
      *new_ptr++ = (uchar)((31 * old_ptr[0] + 61 * old_ptr[1] + 8 * old_ptr[2]) / 100);
      if (d() > 3) *new_ptr++ = old_ptr[3];
    }


  if (alloc_array) delete[] (uchar *)array;

  array       = new_array;
  alloc_array = 1;

  ld(0);
  d(new_d);
}
