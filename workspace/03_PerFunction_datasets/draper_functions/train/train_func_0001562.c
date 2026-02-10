setObjectAt(int x, int y, Object &o)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
		kDebug() << "Inexistent place accessed: (" << x << ", " << y << ")";

		return;
	}

	m_playfield[x * m_height + y] = o;
	o.setCoordinates(x, y);
}
