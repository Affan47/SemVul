highlight(QGraphicsScene* scene, ONU* onu, const QColor& color, qreal opacity)
{
  kDebug() << m_name << color << opacity;
  if (m_highlighting_locked)
  {
    return;
  }
  clearHighlighting();

  QDomNode countryElement = onu->svgDom()->elementById(m_name);
  if (countryElement.isNull())
  {
    kWarning() << "Got a null element" << endl;
    return;
  }


  onu->svgDom()->setCurrentNode(countryElement);
  onu->svgDom()->setStyleProperty("fill", color.name());
  onu->svgDom()->setStyleProperty("fill-opacity", QString::number(opacity));


  QByteArray svg = onu->svgDom()->nodeToByteArray();
  m_renderer->load(svg);


  m_highlighting = new QGraphicsSvgItem();
  m_highlighting->setSharedRenderer(m_renderer);
  m_highlighting->setElementId(m_name);
  kDebug() << "anchor point=" << m_anchorPoint;
  kDebug() << "set highlighting pos to " << (m_anchorPoint.x()-m_highlighting->boundingRect().width()/2)
  << (m_anchorPoint.y()-m_highlighting->boundingRect().height()/2) ;
  m_highlighting->setPos(
      (m_anchorPoint.x()-m_highlighting->boundingRect().width()/2),
      (m_anchorPoint.y()-m_highlighting->boundingRect().height()/2));
  m_highlighting->setZValue(5);
  scene->addItem(m_highlighting);


}
