Add(const Point &P, const Point &Q) const
{
	if (P.identity) return Q;
	if (Q.identity) return P;
	if (Equal(P, Q)) return Double(P);
	if (m_field->Equal(P.x, Q.x) && m_field->Equal(P.y, m_field->Add(Q.x, Q.y))) return Identity();

	FieldElement t = m_field->Add(P.y, Q.y);
	t = m_field->Divide(t, m_field->Add(P.x, Q.x));
	FieldElement x = m_field->Square(t);
	m_field->Accumulate(x, t);
	m_field->Accumulate(x, Q.x);
	m_field->Accumulate(x, m_a);
	m_R.y = m_field->Add(P.y, m_field->Multiply(t, x));
	m_field->Accumulate(x, P.x);
	m_field->Accumulate(m_R.y, x);

	m_R.x.swap(x);
	m_R.identity = false;
	return m_R;
}
