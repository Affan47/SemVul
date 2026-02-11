set_input(const GRect &rect)
{
  if (rect.isempty())
    G_THROW( ERR_MSG("GRect.empty_rect1") );
  rectFrom = rect;
  if (code & SWAPXY)
  {
    iswap(rectFrom.xmin, rectFrom.ymin);
    iswap(rectFrom.xmax, rectFrom.ymax);
  }
  rw = rh = GRatio();
}
