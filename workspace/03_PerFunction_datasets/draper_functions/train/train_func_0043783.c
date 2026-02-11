which(int event_x, int event_y) {
  if (children() == 0) return 0;
  int H = tab_height();
  if (H < 0) {
    if (event_y > y()+h() || event_y < y()+h()+H) return 0;
  } else {
    if (event_y > y()+H || event_y < y()) return 0;
  }
  if (event_x < x()) return 0;
  Fl_Widget *ret = 0L;
  int nc = children();
  tab_positions();
  for (int i=0; i<nc; i++) {
    if (event_x < x()+tab_pos[i+1]) {
      ret = child(i);
      break;
    }
  }
  return ret;
}
