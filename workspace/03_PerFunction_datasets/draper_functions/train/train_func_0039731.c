draw() {
  if (damage()&~FL_DAMAGE_CHILD) input.clear_damage(FL_DAMAGE_ALL);
  input.box(box());
  input.color(color(), selection_color());
  Fl_Widget *i = &input; i->draw();
  input.clear_damage();
}
