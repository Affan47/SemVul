createNewLine(QPointF startPoint)
{
	QPointF qtPoint;


	GLELine *currentLine = new GLELine(dpi, pixmap.size(), this);

	objectList.append(currentLine);

	currentIndex = objectList.size() - 1;


	connect(this, SIGNAL(sizeChanged(QSize,double)),
			objectList[currentIndex], SLOT(setPixmapSize(QSize,double)));

	objectList[currentIndex]->setPoint(GLELine::StartPoint,
			startPoint);
	objectList[currentIndex]->setPoint(GLELine::EndPoint,
			startPoint);

	objectList[currentIndex]->setGLEObject(gleScript->newGLEObject(GDOLine));
	objectList[currentIndex]->setLineProperties();


	isDrawing = true;

}
