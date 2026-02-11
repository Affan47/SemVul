draw() {
  if (type() == FL_HIDDEN_BUTTON) return;
  Fl_Color col = value() ? selection_color() : color();
  draw_box(value() ? (down_box()?down_box():fl_down(box())) : box(), col);
  draw_backdrop();
  if (labeltype() == FL_NORMAL_LABEL && value()) {
    Fl_Color c = labelcolor();
    labelcolor(fl_contrast(c, col));
    draw_label();
    labelcolor(c);
  } else draw_label();
  if (Fl::focus() == this) draw_focus();
}
