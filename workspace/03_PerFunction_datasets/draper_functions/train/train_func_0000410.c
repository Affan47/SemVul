fl_gap() {
  while (n>gap+2 && p[n-1].x == p[gap].x && p[n-1].y == p[gap].y) n--;
  if (n > gap+2) {
    fl_transformed_vertex((COORD_T)p[gap].x, (COORD_T)p[gap].y);
#ifdef WIN32
    counts[numcount++] = n-gap;
#endif
    gap = n;
  } else {
    n = gap;
  }
}
