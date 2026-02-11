GetFusedBonds ()
{
	int n = 0;
	std::map<Atom*, ChainElt>::iterator i, end = m_Bonds.end ();
	for (i = m_Bonds.begin (); i != end; i++)
		if ((*i).second.fwd->IsCyclic() > 1) n++;
	return n;
}
