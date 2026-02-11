getFontMetrics(float * pAscent, float * pDescent,
		float * pEmSquare)
{
	if (pEmSquare)
		*pEmSquare = m_emSquare * m_xScale;
	if (pAscent)
		*pAscent = m_ascent * m_yScale;
	if (pDescent)
		*pDescent = m_descent * m_yScale;
}
