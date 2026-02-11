GetAngle2DRad (Atom* pAtom)
{
	double x1, y1, x2, y2;
	m_Begin->GetCoords (&x1, &y1);
	m_End->GetCoords (&x2, &y2);
	x2 -= x1;
	y2 -= y1;
	double length = square (x2) + square (y2);
	if (length == 0.0)
		return HUGE_VAL;
	if (pAtom == m_Begin)
		return atan2 (-y2, x2);
	else if (pAtom == m_End)
		return atan2 (y2, -x2);
	return HUGE_VAL;
}
