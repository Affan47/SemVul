CanvasRectMovable(double x, double y, double width, double height)
: Goocanvas::Rect(x, y, width, height),
  m_snap_corner(CORNER_ALL)
{
  init();
}
