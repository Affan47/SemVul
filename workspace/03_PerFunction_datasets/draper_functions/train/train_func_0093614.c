doClear() {
	PartsBinView::doClear();
	m_layout->clear();
	delete m_layouter;
	delete scene();
	setScene(new QGraphicsScene(this));
	setupLayout();
}
