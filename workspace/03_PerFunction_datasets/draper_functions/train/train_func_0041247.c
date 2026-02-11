create_line_at_mouse_pos(void)
{
  Bool on_same_screen;
  Window root, child;
  int rx, ry, x, y;
  unsigned int mask;

  on_same_screen =
    XQueryPointer(display, XtWindow(map_canvas),
		  &root, &child,
		  &rx, &ry,
		  &x, &y,
		  &mask);

  if (on_same_screen) {
    update_line(x, y);
  }
}
