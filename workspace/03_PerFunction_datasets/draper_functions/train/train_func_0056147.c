wsrch FUNCTION((w, low, high), char *w AND int low AND int high)
{
  int i, j;

  for (;;) {
    i = (low + high) / 2;
    if ((j = strncmp(w, Wp[i], 4)) == 0)
      return i;
    if (high == low + 1) {

      if (strncmp(w, Wp[high], 4) == 0)
	return high;
      else
	return -1;
    }
    if (low >= high)
      return -1;
    if (j < 0)
      high = i;
    else
      low = i;
  }
}
