findCompletedRows()
{

	KDiamond::Color currentColor;
	QList<QPoint> diamonds;
	int x, y, xh, yh;
	const int gridSize = m_board->gridSize();
#define C(X, Y) m_board->diamond(QPoint(X, Y))->color()

	for (y = 0; y < gridSize; ++y)
	{
		for (x = 0; x < gridSize - 2; ++x)
		{
			currentColor = C(x, y);
			if (currentColor != C(x + 1, y))
				continue;
			if (currentColor != C(x + 2, y))
				continue;

			diamonds << QPoint(x, y);
			diamonds << QPoint(x + 1, y);
			diamonds << QPoint(x + 2, y);

			if (x + 3 >= gridSize)
			{

				x += 2;
				continue;
			}
			for (xh = x + 3; xh <= gridSize - 1; ++xh)
			{
				if (currentColor == C(xh, y))
					diamonds << QPoint(xh, y);
				else
					break;
			}
			x = xh - 1;
		}
	}

	for (x = 0; x < gridSize; ++x)
	{
		for (y = 0; y < gridSize - 2; ++y)
		{
			currentColor = C(x, y);
			if (currentColor != C(x, y + 1))
				continue;
			if (currentColor != C(x, y + 2))
				continue;
			diamonds << QPoint(x, y);
			diamonds << QPoint(x, y + 1);
			diamonds << QPoint(x, y + 2);
			if (y + 3 >= gridSize)
			{
				y += 2;
				continue;
			}
			for (yh = y + 3; yh <= gridSize - 1; ++yh)
			{
				if (currentColor == C(x, yh))
					diamonds << QPoint(x, yh);
				else
					break;
			}
			y = yh - 1;
		}
	}
#undef C
	return diamonds;
}
