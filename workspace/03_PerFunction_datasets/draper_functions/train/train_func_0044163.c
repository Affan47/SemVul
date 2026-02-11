get_width_height(double& width, double& height) const
{
  Glib::RefPtr<const Goocanvas::Item> first_child = get_child(0);
  if(!first_child)
  {

    width = m_width;
    height = m_height;
  }
  else
  {
    Glib::RefPtr<const CanvasItemMovable> movable = CanvasItemMovable::cast_const_to_movable(first_child);
    if(movable)
      movable->get_width_height(width, height);
  }


  if(width == -1)
    width = 100;

  if(height == -1)
    height = 100;
}
