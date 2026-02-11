precalc()
{
  if (rectTo.isempty() || rectFrom.isempty())
    G_THROW( ERR_MSG("GRect.empty_rect3") );
  rw = GRatio(rectTo.width(), rectFrom.width());
  rh = GRatio(rectTo.height(), rectFrom.height());
}
