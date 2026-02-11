print_widget(Fl_Widget* widget, int delta_x, int delta_y)
{
  int old_x, old_y, new_x, new_y, is_window;
  if ( ! widget->visible() ) return;
  is_window = (widget->as_window() != NULL);
  widget->damage(FL_DAMAGE_ALL);

  origin(&old_x, &old_y);
  new_x = old_x + delta_x;
  new_y = old_y + delta_y;
  if (!is_window) {
    new_x -= widget->x();
    new_y -= widget->y();
  }
  if (new_x != old_x || new_y != old_y) {
    translate(new_x - old_x, new_y - old_y );
  }

  if (is_window) fl_push_clip(0, 0, widget->w(), widget->h() );

  int drawn_by_plugin = 0;
  if (widget->as_gl_window()) {
    Fl_Plugin_Manager pm("fltk:device");
    Fl_Device_Plugin *pi = (Fl_Device_Plugin*)pm.plugin("opengl.device.fltk.org");
    if (pi) {
      int width, height;
      this->printable_rect(&width, &height);
      drawn_by_plugin = pi->print(widget, 0, 0, height);
    }
  }
  if (!drawn_by_plugin) {
    widget->draw();
  }
  if (is_window) fl_pop_clip();

  traverse(widget);

  if (new_x != old_x || new_y != old_y) {
    untranslate();
  }
}
