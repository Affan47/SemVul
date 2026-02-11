createNewArcFromScript(GLEArcDO* arc) {
	GLEPoint dummy;
	objectList.append(new GLEArc(dpi, pixmap.size(), this));
	currentIndex = objectList.size() - 1;
	connect(this, SIGNAL(sizeChanged(QSize,double)), objectList[currentIndex], SLOT(setPixmapSize(QSize,double)));
	objectList[currentIndex]->setPoint(GLEArc::CentrePoint, gleToQt(arc->getCenter()));
	objectList[currentIndex]->setPoint(GLEArc::StartPoint, gleToQt(arc->getPoint1(dummy)));
	objectList[currentIndex]->setPoint(GLEArc::EndPoint, gleToQt(arc->getPoint2(dummy)));
	objectList[currentIndex]->setPoint(GLEArc::MidPoint, gleToQt(arc->getPointMid(dummy)));
	objectList[currentIndex]->setGLEObject(arc);
	objectList[currentIndex]->setLineProperties();
	objectList[currentIndex]->setPropertyNoUpdate(GLELine::ArrowHeadPresence, arc->getArrow());
}
