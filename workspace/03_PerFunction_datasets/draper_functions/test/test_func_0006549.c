rename_me(Fl_Widget*o) {
  const char *input = fl_input("Input:", o->label());

  if (input) {
    o->copy_label(input);
    o->redraw();
  }
}
