measure() {
  int W, H;


  if (w()<0 && data()) {
    fl_measure_pixmap(data(), W, H);
    w(W); h(H);
  }
}
