setVisible(bool yes)
{
	QGraphicsLineItem::setVisible(yes);
	guideLine->setVisible(m_showGuideLine? yes : false);
}
