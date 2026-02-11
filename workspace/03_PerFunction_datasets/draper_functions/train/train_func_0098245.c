UpdateBounds ()
{

	list <Point>::const_iterator i = m_Points.begin (), end = m_Points.end ();
	if (i == end)
		return;
	m_x0 = m_x1 = (*i).x;
	m_y0 = m_y1 = (*i).y;
	for (i++; i != end; i++) {
		if ((*i).x < m_x0)
			m_x0 = (*i).x;
		else if ((*i).x > m_x1)
			m_x1 = (*i).x;
		if ((*i).y < m_y0)
			m_y0 = (*i).y;
		else if ((*i).y > m_y1)
			m_y1 = (*i).y;
	}
	double lw = GetLineWidth () / 2.;
	m_x0 -= lw;
	m_x1 += lw;
	m_y0 -= lw;
	m_y1 += lw;
	Item::UpdateBounds ();
}
