draw_label() const {
  int X = x_+Fl::box_dx(box());
  int W = w_-Fl::box_dw(box());
  if (W > 11 && align()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}
  draw_label(X, y_+Fl::box_dy(box()), W, h_-Fl::box_dh(box()));
}
