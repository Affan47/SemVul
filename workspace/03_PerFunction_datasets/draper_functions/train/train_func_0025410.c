clipToBoard(QString svgString, ItemBase * board, const QString & layerName, SVG2gerber::ForWhy forWhy, const QString & clipString, bool displayMessageBoxes, QMultiHash<long, ConnectorItem *> & treatAsCircle) {
	QRectF source = board->sceneBoundingRect();
	source.moveTo(0, 0);
	return clipToBoard(svgString, source, layerName, forWhy, clipString, displayMessageBoxes, treatAsCircle);
}
