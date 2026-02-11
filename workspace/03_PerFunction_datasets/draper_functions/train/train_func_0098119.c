invert(void) {
  register unsigned int i, j, wh = (width * height) - 1;
  unsigned char tmp;

  for (i = 0, j = wh; j > i; j--, i++) {
    tmp = *(red + j);
    *(red + j) = *(red + i);
    *(red + i) = tmp;

    tmp = *(green + j);
    *(green + j) = *(green + i);
    *(green + i) = tmp;

    tmp = *(blue + j);
    *(blue + j) = *(blue + i);
    *(blue + i) = tmp;
  }
}
