draw(Painter &painter) const
{
  std::vector<Bezier> bez;
  beziers(bez);
  painter.moveTo(bez.front().iV[0]);
  for (uint i = 0; i < bez.size(); ++i)
    painter.curveTo(bez[i]);
  painter.closePath();
}
