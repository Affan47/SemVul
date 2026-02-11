Insert (Atom* pAtom1, Atom* pAtom2, Chain& chain)
{

	if (m_Bonds[pAtom1].rev->GetOrder () == 2)
		m_Bonds[pAtom1].rev->SetDirty (true);
	m_Bonds[pAtom1].fwd = ((Cycle&) chain).m_Bonds[pAtom1].fwd;
	m_Bonds[pAtom1].fwd->AddCycle (this);
	Atom *pAtom = (Atom*) m_Bonds[pAtom1].fwd->GetAtom (pAtom1);
	while (pAtom != pAtom2) {
		m_Bonds[pAtom] = ((Cycle&) chain).m_Bonds[pAtom];
		m_Bonds[pAtom].fwd->AddCycle (this);
		pAtom = (Atom*) m_Bonds[pAtom].fwd->GetAtom (pAtom);
	}
	m_Bonds[pAtom2].rev = ((Cycle&) chain).m_Bonds[pAtom2].rev;
	if (m_Bonds[pAtom2].fwd->GetOrder () == 2) m_Bonds[pAtom2].fwd->SetDirty (true);
}
