newGame(int columns, int rows, int balls)
{
	m_columns = columns;
	m_rows = rows;

	m_ballsOutside->clear();

	m_ballToPlace = balls;
	scale(1./m_width, 1./m_height);


	m_height = (rows/2);
	if (rows % 2 > 0)
		m_height++;
	m_width = balls/m_height;
	if (balls % m_height > 0)
		m_width++;

	scale(m_width/1., m_height/1.);

	setPos((-(m_width+1)*KBBScalableGraphicWidget::RATIO), KBBScalableGraphicWidget::RATIO);

	fillBallsOutside(0);
}
