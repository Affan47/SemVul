Equal(const Point &P, const Point &Q) const
{
	if (P.identity && Q.identity)
		return true;

	if (P.identity && !Q.identity)
		return false;

	if (!P.identity && Q.identity)
		return false;

	return (m_field->Equal(P.x,Q.x) && m_field->Equal(P.y,Q.y));
}
