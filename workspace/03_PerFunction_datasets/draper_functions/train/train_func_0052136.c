xycnva4 (short ix, short iy, float *x, float *y) {

  if (rotflg) {
    *x = ((float)ix)/1000.0;
    *y = ((float)iy)/1025.6;
  } else {
    *x = 8.5 - ((float)iy)/1000.0;
    *y = ((float)ix)/1025.6;
  }
  *x = bwide + *x*((8.5-bwide*2.0)/8.5);
  *y = bwide + *y*((11.0-bwide*2.0)/11.0);
}
