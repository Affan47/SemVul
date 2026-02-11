paintEvent(QPaintEvent*)
{
	QPainter p(this);
	const unsigned int arrowSize = 8;
	const unsigned int margin = 2;

	QStyleOptionFrame opt;
	opt.init(this);
	opt.lineWidth    = 2;
	opt.midLineWidth = 0;

	p.fillRect( rect(), palette().brush( QPalette::Background ) );

	style()->drawPrimitive( QStyle::PE_Frame, &opt, &p, this);

	if (d->arrow == Qt::NoArrow)
		return;

	if (static_cast<unsigned int>(width()) < arrowSize + margin ||
	    static_cast<unsigned int>(height()) < arrowSize + margin)
		return;

	unsigned int x = 0, y = 0;
	if (d->arrow == Qt::DownArrow) {
		x = (width() - arrowSize) / 2;
		y = height() - (arrowSize + margin);
	} else if (d->arrow == Qt::UpArrow) {
		x = (width() - arrowSize) / 2;
		y = margin;
	} else if (d->arrow == Qt::RightArrow) {
		x = width() - (arrowSize + margin);
		y = (height() - arrowSize) / 2;
	} else {
		x = margin;
		y = (height() - arrowSize) / 2;
	}

	if (isDown()) {
		x++;
		y++;
	}

	QStyle::PrimitiveElement e = QStyle::PE_IndicatorArrowLeft;
	switch (d->arrow)
	{
		case Qt::LeftArrow: e = QStyle::PE_IndicatorArrowLeft; break;
		case Qt::RightArrow: e = QStyle::PE_IndicatorArrowRight; break;
		case Qt::UpArrow: e = QStyle::PE_IndicatorArrowUp; break;
		case Qt::DownArrow: e = QStyle::PE_IndicatorArrowDown; break;
		case Qt::NoArrow: assert( 0 ); break;
	}

	opt.state |= QStyle::State_Enabled;
	opt.rect   = QRect( x, y, arrowSize, arrowSize);

	style()->drawPrimitive( e, &opt, &p, this );
}
