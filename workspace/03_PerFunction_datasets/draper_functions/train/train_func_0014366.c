ReplaceAtom (Atom* oldAtom, Atom* newAtom)
{
	if (oldAtom == m_Begin) {
		if (m_End)
			m_End->RemoveBond (this);
		m_Begin = newAtom;
		if (m_Begin && m_End)
			m_End->AddBond (this);
	} else if (oldAtom == m_End) {
		if (m_Begin)
			m_Begin->RemoveBond (this);
		m_End = newAtom;
		if (m_Begin && m_End)
			m_Begin->AddBond (this);
	}
	return true;
}
