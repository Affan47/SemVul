calculateScaleRatios(QPointF basePoint, QPointF startPoint, QPointF endPoint, int method)
{
	QPointF oldSize = startPoint - basePoint;
	QPointF newSize = endPoint - basePoint;
	double yscale, xscale;

	switch (method)
	{
		case ProportionalScale:
			if (oldSize.x() == 0.0)
				xscale = 1e6;
			else
				xscale = newSize.x() / oldSize.x();

			if (oldSize.y() == 0.0)
				yscale = 1e6;
			else
				yscale = newSize.y() / oldSize.y();

			if (xscale > yscale)
				yscale = xscale;
			else
				xscale = yscale;
			break;


		case HorizontalScale:
			yscale = 1.0;
			if (oldSize.x() == 0.0)
				xscale = 1.0;
			else
				xscale = newSize.x() / oldSize.x();
			break;

		case VerticalScale:
			xscale = 1.0;
			if (oldSize.y() == 0.0)
				yscale = 1.0;
			else
				yscale = newSize.y() / oldSize.y();
			break;


		default:
			xscale = yscale = 1.0;
	}

	return(QPointF(xscale, yscale));
}
