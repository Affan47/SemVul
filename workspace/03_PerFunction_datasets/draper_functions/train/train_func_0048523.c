draw_child(Fl_Widget& widget) const {
  if (widget.visible() && widget.type() < FL_WINDOW &&
      fl_not_clipped(widget.x(), widget.y(), widget.w(), widget.h())) {
    widget.clear_damage(FL_DAMAGE_ALL);
    widget.draw();
    widget.clear_damage();
  }
}
