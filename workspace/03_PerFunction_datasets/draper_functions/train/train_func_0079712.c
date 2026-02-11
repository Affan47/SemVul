OnLoaded ()
{
	if (m_Begin && m_End) {
		m_Begin->AddBond (this);
		m_End->AddBond (this);
	}
}
