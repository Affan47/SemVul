pt_in_rect (icoords pt, GdkRectangle rect)
{
  return ((pt.x >= rect.x) && (pt.x <= rect.x + rect.width)
          && (pt.y >= rect.y) && (pt.y <= rect.y + rect.height));
}
