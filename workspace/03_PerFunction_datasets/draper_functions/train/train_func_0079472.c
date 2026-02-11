a2_hplot(apple2_state_t *st, int hcolor, int x, int y)
{
  int highbit,run;

  highbit=((hcolor<<5)&0x80) ^ 0x80;

  if (y<0 || y>=192 || x<0 || x>=280) return;

  for (run=0; run<2 && x<280; run++) {
    unsigned char *vidbyte = &st->hireslines[y][x/7];
    unsigned char whichbit=1<<(x%7);
    int masked_bit;

    *vidbyte = (*vidbyte & 0x7f) | highbit;


    masked_bit = (hcolor>>(1-(x&1)))&1;


    *vidbyte = (*vidbyte & ~whichbit) | (masked_bit ? whichbit : 0);

    x++;
  }
}
