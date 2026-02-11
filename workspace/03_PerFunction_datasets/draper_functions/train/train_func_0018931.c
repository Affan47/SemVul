paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_hidden || m_layerHidden) return;

	ItemBase::paint(painter, option, widget);
}
