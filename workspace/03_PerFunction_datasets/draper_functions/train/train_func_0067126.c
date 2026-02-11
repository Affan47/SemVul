endLayer()
{
  if (isCollecting())
  {
    assert(m_pageOpened);
    assert(m_layerOpened);

    KEYCollectorBase::endLayer();

    m_layerOpened = false;
    m_painter->endLayer();
  }
}
