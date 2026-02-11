GetBond (Atom* pAtom) const
{
	std::map<Atom*, Bond*>::const_iterator i;
	i = m_Bonds.find (pAtom);
	return (i != m_Bonds.end ())? (*i).second: NULL;
}
