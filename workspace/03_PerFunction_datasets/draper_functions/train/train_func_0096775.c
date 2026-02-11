sketchWidgets()
{
	QList<SketchWidget *> list;
	list << m_breadboardGraphicsView << m_schematicGraphicsView << m_pcbGraphicsView;
	return list;
}
