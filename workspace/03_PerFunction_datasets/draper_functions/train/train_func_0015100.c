fl_subimage_offsets(int a, int aw, int b, int bw, int &obw)
{
  int off;
  int ob;

  if (b >= a) {
    ob = b;
    off = 0;
  } else {
    ob = a;
    off = a - b;
  }

  bw -= off;

  if (ob + bw <= a + aw) {
    obw = bw;
  } else {
    obw = (a + aw) - ob;
  }

  return off;
}
