read_liftblock(const short *coeff, IW44Image::Map *map)
{
  int n=0;
  for (int n1=0; n1<64; n1++)
    {
      short *d = data(n1,map);
      for (int n2=0; n2<16; n2++,n++)
        d[n2] = coeff[zigzagloc[n]];
    }
}
