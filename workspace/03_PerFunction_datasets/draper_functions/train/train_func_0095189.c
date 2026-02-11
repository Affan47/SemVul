draw() {
  draw_box();
  if (!menu() || !menu()->text) return;
  const Fl_Menu_Item* m;
  int X = x()+6;
  for (m=menu()->first(); m->text; m = m->next()) {
    int W = m->measure(0,this) + 16;
    m->draw(X, y(), W, h(), this);
    X += W;
    if (m->flags & FL_MENU_DIVIDER) {
      int y1 = y() + Fl::box_dy(box());
      int y2 = y1 + h() - Fl::box_dh(box()) - 1;


      fl_color(FL_DARK3);
      fl_yxline(X - 6, y1, y2);
      fl_color(FL_LIGHT3);
      fl_yxline(X - 5, y1, y2);
    }
  }
}
