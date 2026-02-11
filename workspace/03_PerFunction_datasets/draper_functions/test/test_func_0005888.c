Spanningelt_setup (int index1part_in, int index1interval_in) {
  index1part = index1part_in;
  index1interval = index1interval_in;

  spansize = 0;
  while (spansize + index1interval_in < index1part) {
    spansize += index1interval_in;
  }
  spansize += index1interval_in;

  return spansize;
}
