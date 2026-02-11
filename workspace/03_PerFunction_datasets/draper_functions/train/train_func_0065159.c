ewmh_supported() {
  static int result = -1;

  if (result == -1) {
    result = 0;
    unsigned long nitems;
    unsigned long *words = 0;
    if (0 == get_xwinprop(XRootWindow(fl_display, fl_screen), fl_NET_SUPPORTING_WM_CHECK, 64,
                          &nitems, &words) && nitems == 1) {
      Window child = words[0];
      if (0 == get_xwinprop(child, fl_NET_SUPPORTING_WM_CHECK, 64,
                           &nitems, &words) && nitems == 1) {
        result = (child == words[0]);
      }
    }
  }

  return result;
}
