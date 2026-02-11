setupTravel(
    GameLogic::Country* src,
    GameLogic::Country* dest,
    const QPointF* dpi)
{
  if (dpi ==0)
  {
    AnimSprite::setupTravel(src, dest, src->pointInfantry()*m_zoom, dest-> pointInfantry()*m_zoom);
  }
  else
  {
    AnimSprite::setupTravel(src, dest, src->pointInfantry()*m_zoom, *dpi);
  }
}

}
