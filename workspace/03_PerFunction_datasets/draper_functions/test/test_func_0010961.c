symbol_cb(Fl_Widget *,void *) {
  text->labeltype(FL_SYMBOL_LABEL);
  if (input->value()[0] != '@') {
    input->static_value("@->");
    text->label("@->");
  }
  window->redraw();
}
