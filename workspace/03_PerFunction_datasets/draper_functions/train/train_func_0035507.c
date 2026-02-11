drawGrid(QPainter* paint)
{

	if ((gridSpacing.x() == 0.0) || (gridSpacing.y() == 0.0) || (dpi == 0.0) || (areaSize.height() == 0))
	{
		return;
	}


	QPointF qtGrid = QGLE::relGLEToQt(gridSpacing, dpi);


	int nbX = (int)floor(areaSize.width()/qtGrid.x()+1.0);
	int nbY = (int)floor(areaSize.height()/qtGrid.y()+1.0);
	for (int x = 0; x < nbX; x ++)
	{
		double xp = GS_OFFSET*dpi + x*qtGrid.x();
		for (int y = 0; y < nbY; y++)
		{
			double yp = GS_OFFSET*dpi + y*qtGrid.y();
			paint->drawPoint(QPointF(xp, areaSize.height() - yp));
		}
	}
}
