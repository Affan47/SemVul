zig_zag_reorder(int block[])
{
  int n, x, y;
  int copy[64];

  for (n = 0; n < 64; n++)
    copy[n] = block[n];

  n = x = y = 0;
  while (n < 63) {

    if (x < 7)
      x++;
    else
      y++;
    block[x + (y * 8)] = copy[++n];


    while (x > 0 && y < 7) {
      x--;
      y++;
      block[x + (y * 8)] = copy[++n];
    }


    if (y < 7)
      y++;
    else
      x++;
    block[x + (y * 8)] = copy[++n];


    while (y > 0 && x < 7) {
      y--;
      x++;
      block[x + (y * 8)] = copy[++n];
    }
  }
}
