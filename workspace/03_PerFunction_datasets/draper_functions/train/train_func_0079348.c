mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::RightButton) {
		int idx = tabAt(e->pos());
		QWidget* page = 0;
		if (idx >=0) {
			setCurrentIndex(idx);
			page = _tabWidget->widget(idx);
		}
		context(page, e->globalPos());
	}
	QTabBar::mousePressEvent(e );
}
